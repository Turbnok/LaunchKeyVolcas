
#include <application.hpp>
#include <Screen.hpp>
#include <Sequencer.hpp>

#include <MenuState.hpp>
#include <unistd.h>

#include <iostream>
#include <chrono>
#include <thread>
#include <functional>

void Application::InitMIDI(void)
{
    midiOut = std::make_shared<MidiOut>();
    midiLaunch = std::make_shared<MidiOut>();
    midiClock = std::make_shared<MidiClock>();
    midiPads = std::make_shared<MidiIn>();
    midiKeys = std::make_shared<MidiIn>();

    std::cout << "Midi In: " << std::endl;
    auto ports = midiClock->GetPorts();
    for (unsigned int i = 0; i < ports.size(); ++i)
    {
        std::cout << "Port id: " << i << " name: " << ports.at(i) << std::endl;
    }
    std::cout << "Midi Out: " << std::endl;
    ports = midiOut->GetPorts();
    for (unsigned int i = 0; i < ports.size(); ++i)
    {
        std::cout << "Port id: " << i << " name: " << ports.at(i) << std::endl;
    }
    // midiClock->OpenPort(1,"Clock");

    midiKeys->OpenPort(2, "Keys");
    midiPads->OpenPort(3, "Pads");
    midiLaunch->OpenPort(3, "LaunchKey");

    midiLaunch->SendMidiMessage(LaunchKey::DAWModeOn);
    midiLaunch->SendMidiMessage(LaunchKey::PadModeDrum);
    midiOut->OpenPort(1, "Out");
}

void Application::Init(void)
{

    std::cout << "Play - exit" << std::endl;
    InitMIDI();
    MenuState *currentState_ = new MenuState;
    screen.setMidiOut(midiOut.get());
    screen.setLaunchKey(midiLaunch.get());
    // screen.setClock()
    screen.setState(currentState_);
}

void Application::Touch(std::optional<MidiMessage> message)
{

    if (!message)
        return;
    screen.receiveMidi(*message);
}

void Application::MIDILoop(void)
{

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
        // midiOut->SendMidiMessage(*messagePads);
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

        if (messageKeys->status != 224 && messageKeys->status != 176)
        {
            // pitch or modulation
            if (messageKeys->status == MidiStatus::NOF)
            {
                MidiMessage hello = MidiMessage(MidiChannel::CH1, MidiStatus::NOF, messageKeys->data1.value(), 0);
                midiOut->SendMidiMessage(hello);
            }
            else
            {
                MidiMessage hello = MidiMessage(MidiChannel::CH1, MidiStatus::NON, messageKeys->data1.value(), messageKeys->data2.value());
                midiOut->SendMidiMessage(hello);
            }
        }
    }

    Touch(messagePads);
}

void Application::Run(void)
{

    do
    {
        MIDILoop();
        
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

    MidiMessage message = LaunchKey::Play;
    message.channel = MidiChannel::CH2;
    message.data2 = LaunchKey::Brightness::P0;
    midiLaunch->SendMidiMessage(message);
    midiLaunch->SendMidiMessage(LaunchKey::DAWModeOff);
}

void do_something()
{
    std::cout << "I am doing something" << std::endl;
}
