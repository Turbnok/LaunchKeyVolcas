#include <application.hpp>
#include <Screen.hpp>
#include <MenuState.hpp>
#include <unistd.h>

void
Application::InitMIDI(void)
{
    midiOut =   std::make_shared<MidiOut>();
    midiLaunch =  std::make_shared<MidiOut>();
    midiPads  =   std::make_shared<MidiIn>();
    midiKeys  =   std::make_shared<MidiIn>();
   
    std::cout << "Midi In: " << std::endl;
    auto ports = midiOut->GetPorts();
    for (unsigned int i = 0; i < ports.size(); ++i){
		std::cout << "Port id: " << i << " name: " << ports.at(i) << std::endl;
    }
        
	midiKeys->OpenPort(1);
    midiPads->OpenPort(2); 
    midiLaunch->OpenPort(2);
    
    midiLaunch->SendMidiMessage(LaunchKey::DAWModeOn);
    midiLaunch->SendMidiMessage(LaunchKey::PadModeDrum);
	
	midiOut->OpenPort(3);
		
	
	
}

void
Application::Init(void)
{
	
    std::cout << "Play - exit" << std::endl;
	InitMIDI();
    
    MenuState* currentState_ = new MenuState;
    screen.setMidiOut(midiOut.get());
    screen.setLaunchKey(midiLaunch.get());
    screen.setState(currentState_);
       
}

void
Application::initialState(int state){
	if(state == 1){	
		
    }else if(state == 2){
		MidiMessage colMessage = LaunchKey::DrumPadColor;
        colMessage.data2   =   0;
		for (int i = 0; i < 4; ++i)
        {
            colMessage.data1   =   LaunchKey::DrumPads::DP1 + i;
            midiLaunch->SendMidiMessage(colMessage);
        }
        colMessage.data2   =   0;
        for (int i = 0; i < 4; ++i)
        {
            colMessage.data1   =   LaunchKey::DrumPads::DP5 + i;
            midiLaunch->SendMidiMessage(colMessage);
        }
        int colors[4] = {9,9,9,9};
        for (int i = 0; i < 4; ++i)
        {
			colMessage.data2   =   colors[i];
            colMessage.data1   =   LaunchKey::DrumPads::DP9 + i;
            midiLaunch->SendMidiMessage(colMessage);
        }
        colors[0] = 9;
        colors[1] = 0;
        colors[2] = 0;
        colors[3] = 0;
        for (int i = 0; i < 4; ++i)
        {
			colMessage.data2   =   colors[i];
            colMessage.data1   =   LaunchKey::DrumPads::DP13 + i;
            midiLaunch->SendMidiMessage(colMessage);
        }	
	}    
}

void
Application::Touch(std::optional<MidiMessage> message)
{
    if (!message) return;	
	screen.receiveMidi(*message);	
}

void
Application::MIDILoop(void)
{
    std::optional<MidiMessage>  messagePads = midiPads->GetMidiMessage();
    
    if (messagePads)
    {
        if (CompareMidiMessage(*messagePads, LaunchKey::ArrUp))
            isPlaying = false;

        if (!messagePads->data2)
        {
            std::cout   << "channel: " << messagePads->channel
                        << " status: " << messagePads->status
                        << " data1: " << messagePads->data1.value() << std::endl;
        }
        else
        {
            std::cout   << "channel: " << messagePads->channel
                        << " status: " << messagePads->status
                        << " data1: " << messagePads->data1.value()
                        << " data2: " << messagePads->data2.value() << std::endl;
        }
        //midiOut->SendMidiMessage(*messagePads);
    }
	std::optional<MidiMessage>  messageKeys = midiKeys->GetMidiMessage();
    if (messageKeys)
    {
        if (!messageKeys->data2)
        {
            std::cout   << "channel: " << messageKeys->channel
                        << " status: " << messageKeys->status
                        << " data1: " << messageKeys->data1.value() << std::endl;
        }
        else
        {
            std::cout   << "channel: " << messageKeys->channel
                        << " status: " << messageKeys->status
                        << " data1: " << messageKeys->data1.value()
                        << " data2: " << messageKeys->data2.value() << std::endl;
        }
        if(messageKeys->status==MidiStatus::NOF){
			MidiMessage hello = MidiMessage(MidiChannel::CH1,MidiStatus::NOF, messageKeys->data1.value(),0);
			midiOut->SendMidiMessage(hello);
		}else{
			MidiMessage hello = MidiMessage(MidiChannel::CH1,MidiStatus::NON, messageKeys->data1.value(),messageKeys->data2.value());
			midiOut->SendMidiMessage(hello);
		}
    }
  
    Touch(messagePads);
 }

void
Application::Run(void)
{
    do
    {
        MIDILoop();
    }
    while (isPlaying);

    {
		
        MidiMessage colMessage = LaunchKey::DrumPadColor;
        colMessage.data2   =   0;
        for (int i = 0; i < 4; ++i)
        {
            colMessage.data1   =   LaunchKey::DrumPads::DP1 + i;
            midiLaunch->SendMidiMessage(colMessage);
        }

        for (int i = 0; i < 4; ++i)
        {
            colMessage.data1   =   LaunchKey::DrumPads::DP5 + i;
            midiLaunch->SendMidiMessage(colMessage);
        }

        for (int i = 0; i < 4; ++i)
        {
            colMessage.data1   =   LaunchKey::DrumPads::DP9 + i;
            midiLaunch->SendMidiMessage(colMessage);
        }

        for (int i = 0; i < 4; ++i)
        {
            colMessage.data1   =   LaunchKey::DrumPads::DP13 + i;
            midiLaunch->SendMidiMessage(colMessage);
        }
    }
    {
        MidiMessage colMessage = LaunchKey::SessionPadColor;
        colMessage.data2   =   0;
        for (int i = 0; i < 8; ++i)
        {
            colMessage.data1   =   LaunchKey::SessionPads::SP1 + i;
            midiLaunch->SendMidiMessage(colMessage);
        }
        for (int i = 0; i < 8; ++i)
        {
            colMessage.data1   =   LaunchKey::SessionPads::SP9 + i;
            midiLaunch->SendMidiMessage(colMessage);
        }
    }

    MidiMessage message = LaunchKey::Play;
    message.channel = MidiChannel::CH2;
    message.data2 = LaunchKey::Brightness::P0;
    midiLaunch->SendMidiMessage(message);
    midiLaunch->SendMidiMessage(LaunchKey::DAWModeOff);
}

