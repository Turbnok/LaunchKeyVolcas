
#include <application.hpp>
#include <Screen.hpp>
#include <Sequencer.hpp>

#include <MenuState.hpp>
#include <unistd.h>
#include <Config.hpp>

#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include <fstream>
/*
void Application::bindPorts(void){

}
*/

 
void Application::InitMIDI(void)
{
    midiOut = std::make_shared<MidiOut>();
    midiClock = std::make_shared<MidiClock>();
    sequencer = std::make_shared<Sequencer>();
    midiLaunch = std::make_shared<MidiOut>();
    midiPads = std::make_shared<MidiIn>();
    midiKeys = std::make_shared<MidiIn>();

    std::cout << "Midi In: " << std::endl;
    auto ports = midiLaunch->GetPorts();
    int midiKeysInPort = -1;
    int midiLaunchPort = -1;

    for (unsigned int i = 0; i < ports.size(); ++i)
    {
        std::cout << "Port id: " << i << " name: " << ports.at(i) << std::endl;
        std::string en = ports.at(i);
        int ind = en.find("Launchkey Mini MK3");
        if (ind != -1)
        {
            ind = en.find(":0");
            if (ind != -1)
            {
                midiKeysInPort = i;
            }
            ind = en.find(":1");
            if (ind != -1)
            {
                midiLaunchPort = i;
            }
        }
    }
    ports = midiOut->GetPorts();
    for (unsigned int i = 0; i < ports.size(); ++i)
    {
        std::cout << "Port id: " << i << " name: " << ports.at(i) << std::endl;
        std::string en = ports.at(i);
        int ind = en.find("Launchkey Mini MK3");
        if (ind != -1)
        {
            ind = en.find(":0");
            if (ind != -1)
            {
                midiKeysInPort = i;
            }
            ind = en.find(":1");
            if (ind != -1)
            {
                midiLaunchPort = i;
            }
        }
    }

    if ((midiKeysInPort == -1) || (midiLaunchPort == -1))
    {
        std::cout << "rien trouvé " << std::endl;
        isPlaying = false;
        return;
    }

    midiKeys->OpenPort(midiKeysInPort, "LMV-Keys");
    midiPads->OpenPort(midiLaunchPort, "LMV-Pads");
    midiLaunch->OpenPort(midiLaunchPort, "LMV-LaunchKey");

    midiLaunch->SendMidiMessage(LaunchKey::DAWModeOn);
    midiLaunch->SendMidiMessage(LaunchKey::PadModeDrum);

    midiClock->OpenPort(Config::getAsInt("MIDI_CLOCK_PORT"), "LMV-Clock");
    midiOut->OpenPort(Config::getAsInt("MIDI_OUT_PORT"), "LMV-Out");
}

void Application::Init(void)
{
    Config::init();
    InitMIDI();
    MenuState *currentState_ = new MenuState;
    screen.setMidiOut(midiOut.get());
    screen.setLaunchKey(midiLaunch.get());
    screen.setMidiClock(midiClock.get());
    screen.setSequencer(sequencer.get());


    //screen.setSequencer(sequencer.get());
    screen.setState(currentState_);
}


void Application::loop(void)
{
    sequencer->update();    
    
    std::optional<MidiMessage> messagePads = midiPads->GetMidiMessage();
    if (messagePads)
    {
        if (CompareMidiMessage(*messagePads, LaunchKey::ArrRight))
            isPlaying = false;

        if (!messagePads->data2)
        {
            std::cout << "channel: " << messagePads->channel
                      << " status: " << messagePads->status
                      << " data1: " << messagePads->data1.value() << std::endl;
        }
        else
        {
            std::cout << "channel: " << messagePads->channel
                      << " status: " << messagePads->status
                      << " data1: " << messagePads->data1.value()
                      << " data2: " << messagePads->data2.value() << std::endl;
        }
        screen.receiveMidi(*messagePads);
        //midiOut->SendMidiMessage(*messagePads);
    }

    std::optional<MidiMessage> messageKeys = midiKeys->GetMidiMessage();
    if (messageKeys)
    {
        if (!messageKeys->data2)
        {
            std::cout << "channel: " << messageKeys->channel
                      << " status: " << messageKeys->status
                      << " data1: " << messageKeys->data1.value() << std::endl;
        }
        else
        {
            std::cout << "channel: " << messageKeys->channel
                      << " status: " << messageKeys->status
                      << " data1: " << messageKeys->data1.value()
                      << " data2: " << messageKeys->data2.value() << std::endl;
        }
        sequencer->receiveKeys(*messageKeys);
        
    }
}

void Application::Run(void)
{

    do
    {
        loop();
      

    } while (isPlaying);

    {

        MidiMessage colMessage = LaunchKey::DrumPadColor;
        colMessage.data2 = 0;
        for (int i = 0; i < 4; ++i)
        {
            colMessage.data1 = LaunchKey::DrumPads::DP1 + i;
            midiLaunch->SendMidiMessage(colMessage);
        }

        for (int i = 0; i < 4; ++i)
        {
            colMessage.data1 = LaunchKey::DrumPads::DP5 + i;
            midiLaunch->SendMidiMessage(colMessage);
        }

        for (int i = 0; i < 4; ++i)
        {
            colMessage.data1 = LaunchKey::DrumPads::DP9 + i;
            midiLaunch->SendMidiMessage(colMessage);
        }

        for (int i = 0; i < 4; ++i)
        {
            colMessage.data1 = LaunchKey::DrumPads::DP13 + i;
            midiLaunch->SendMidiMessage(colMessage);
        }

    }
    {
        MidiMessage colMessage = LaunchKey::SessionPadColor;
        colMessage.data2 = 0;
        for (int i = 0; i < 8; ++i)
        {
            colMessage.data1 = LaunchKey::SessionPads::SP1 + i;
            midiLaunch->SendMidiMessage(colMessage);
        }
        for (int i = 0; i < 8; ++i)
        {
            colMessage.data1 = LaunchKey::SessionPads::SP9 + i;
            midiLaunch->SendMidiMessage(colMessage);
        }

    }
    {
    // notes off
    for (int i = 0; i < 10; ++i){
        MidiMessage noteOff;// =  new MidiMessage();
        noteOff.status = MidiStatus::CC;
        noteOff.data1 = 117+i;
        noteOff.data2 = 1;
        noteOff.channel = MidiChannel::CH1;
        midiOut->SendMidiMessage(noteOff);
    }
    }


    MidiMessage recordMessage =  LaunchKey::Record;//LaunchKey::DrumPadColor;
    recordMessage.data2 = 0;
	midiLaunch->SendMidiMessage(recordMessage);

    MidiMessage message = LaunchKey::Play;
    message.channel = MidiChannel::CH2;
    message.data2 = LaunchKey::Brightness::P0;
    midiLaunch->SendMidiMessage(message);    
    midiLaunch->SendMidiMessage(LaunchKey::DAWModeOff);
}
