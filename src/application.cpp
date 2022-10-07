#include <application.hpp>

#include <unistd.h>

void
Application::InitMIDI(void)
{
    midiOut =   std::make_shared<MidiOut>();
    midiLaunch =   std::make_shared<MidiOut>();
    midiPads  =   std::make_shared<MidiIn>();
    midiKeys  =   std::make_shared<MidiIn>();
    
    std::cout << "Midi In: " << std::endl;
    auto ports = midiOut->GetPorts();
    for (unsigned int i = 0; i < ports.size(); ++i){
        std::cout << "Port id: " << i << " name: " << ports.at(i) << std::endl;
     }
        
	midiKeys->OpenPort(2);
    midiPads->OpenPort(3);
 
    midiLaunch->OpenPort(3);
    midiOut->OpenPort(1);
    
    midiLaunch->SendMidiMessage(LaunchKey::DAWModeOn);
    midiLaunch->SendMidiMessage(LaunchKey::PadModeDrum);
	
	menu = 0;
	mode = 4;
	
    MidiMessage message = LaunchKey::Play;
    message.channel = MidiChannel::CH2;
    message.data2 = 0x01;
    
   
    midiLaunch->SendMidiMessage(message);
}

void
Application::Init(void)
{
    std::cout << "Play - exit" << std::endl;
    InitMIDI();
}

void
Application::initialState(int state){
	if(state == 1){	
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
        int colors[4] = {62,33,72,0};
        for (int i = 0; i < 4; ++i)
        {
			colMessage.data2   =   colors[i];
            colMessage.data1   =   LaunchKey::DrumPads::DP9 + i;
            midiLaunch->SendMidiMessage(colMessage);
        }
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
	
	if(menu == 0){
		menu = 1;
		initialState(1);
		
	}else if(menu==2){
		menu = 3;
		// volca keys
		initialState(2);
		
	}
	
	
	if (message->channel  ==  MidiChannel::CH10 &&
		message->status   ==  MidiStatus::NON &&
		message->data2.value() != 0)
	{   
		if(menu == 1){		
			  std::cout   << "value: " << message->data1.value();
			  std::cout   << "value: " << LaunchKey::DrumPads::DP1;
			if(message->data1.value() == LaunchKey::DrumPads::DP9){
					menu = 2;
				}
			}
		if(menu == 3){		
			MidiMessage colMessage = LaunchKey::DrumPadColorFlash;
			colMessage.data2   =   10;
            colMessage.data1   =   message->data1.value();
            midiLaunch->SendMidiMessage(colMessage);	
		}
	}
}

void
Application::Brightness(void)
{
    static bool init = false;

    if (init) return;
    MidiMessage message = LaunchKey::PadBrightness;

    // up arrow
    message.data1 = 0x68;
    message.data2 = LaunchKey::Brightness::P50;
    midiLaunch->SendMidiMessage(message);

    // down arrow
    message.data1 = 0x69;
    message.data2 = LaunchKey::Brightness::P75;
    midiLaunch->SendMidiMessage(message);

    // record button
    message.data1 = 0x75;
    message.data2 = LaunchKey::Brightness::P100;
    midiLaunch->SendMidiMessage(message);

    message.status = MidiStatus::NON;

    init = true;
}

void
Application::MIDILoop(void)
{
    std::optional<MidiMessage>  messagePads = midiPads->GetMidiMessage();
    if (messagePads)
    {
        if (CompareMidiMessage(*messagePads, LaunchKey::Play))
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
			MidiMessage hello = MidiMessage(MidiChannel::CH10,MidiStatus::NOF, messageKeys->data1.value(),0);
			midiOut->SendMidiMessage(hello);
		}else{
			MidiMessage hello = MidiMessage(MidiChannel::CH10,MidiStatus::NON, messageKeys->data1.value(),messageKeys->data2.value());
			midiOut->SendMidiMessage(hello);
		}
    }
  
    // Touch
    if (mode == 4)
        Touch(messagePads);

    else if (mode == 8)
        Brightness();
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

