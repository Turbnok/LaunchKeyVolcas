#include <Sequencer.hpp>
#include <midi.hpp>

Sequencer::Sequencer(){
	std::cout << "constructor" << std::endl;
}
Sequencer::~Sequencer(){
	std::cout << "deconstructor" << std::endl;
}

void 
Sequencer::init(MidiOut* pLaunchKey,MidiOut* pOut, MidiClock* pClock){
    std::cout << "Sequecer Init" << std::endl;    
	//ScreenState::init(pLaunchKey,pOut,pClock);		
	out = pOut;
  	midiClock = pClock;
  	launchKey = pLaunchKey;
}

void
Sequencer::hide(){
	std::cout << "hide sequencer" <<std::endl;
	shown = false;
}
void
Sequencer::show(){
	std::cout << "sequencer show" <<std::endl;
	shown = true;
	MidiMessage colMessage = LaunchKey::DrumPadColor;
	colMessage.data2   =   0;
	for (int i = 0; i < 16; i++)
	{
		LaunchKey::DrumPads pad = static_cast<LaunchKey::DrumPads>(LaunchKey::PADS[i]);
		colMessage.data1 = pad;
		launchKey->SendMidiMessage(colMessage);
	}
}

void 
Sequencer::update(){
	
    std::chrono::steady_clock::time_point elapsed = std::chrono::steady_clock::now();  
    if ((std::chrono::duration_cast<std::chrono::milliseconds> (elapsed - last).count()) > interval)
    {
		if(shown){
        	MidiMessage colMessage = LaunchKey::DrumPadColor;
			colMessage.data1   =   static_cast<LaunchKey::DrumPads>(LaunchKey::PADS[currentStep]);
			colMessage.data2   =   0;
			launchKey->SendMidiMessage(colMessage);
		}
		currentStep++;
        if (currentStep == totalSteps)
        {
            currentStep = 0;
        }
        last = elapsed;		
		MidiMessage n = msg[currentStep][0];
		if(n.status != MidiStatus::UNDEF){
			std::cout << "hop ? " << std::endl;
			std::cout << "channel: " << n.channel 
                      << " status: " << n.status 
                      << " data2: " << n.data2.value() << std::endl;
			n.channel = MidiChannel::CH1;
			out->SendMidiMessage(n);
		}
		if(shown){
			MidiMessage colMessage = LaunchKey::DrumPadColor;
			colMessage = LaunchKey::DrumPadColor;
			colMessage.data1   =   static_cast<LaunchKey::DrumPads>(LaunchKey::PADS[currentStep]);
			colMessage.data2   =   32;
			launchKey->SendMidiMessage(colMessage);
		}
    }
	
}
void
Sequencer::setRecord(bool pOnOff){
	record = pOnOff;
}

void
Sequencer::receiveKeys(MidiMessage message){
	if(record){
		std::cout << "Sequencer midi message : " << message.channel << std::endl;
		std::cout << "data1 : " << message.data1.value() << std::endl;
		std::cout << "data2 : " << message.data2.value() << std::endl;
		msg[currentStep][0] = message; 	
	}
}
bool
Sequencer::receiveMidi(MidiMessage message){
	std::cout << "Sequencer midi message : " << message.channel << std::endl;
	/*
	std::cout << "menu state midi message : " << message.channel << std::endl;
	std::cout << " : " << message.data1.value() << std::endl;
	if(message.data2.value() ==0) return false;
	if(message.data1.value() == LaunchKey::DrumPads::DP9){

		return true;
	}
	if(message.data1.value() == LaunchKey::DrumPads::DP10){

		return true;
	}
	if(message.channel == 15){
		// pots
		
		tempo =  message.data2.value();
		interval = 60000 / tempo / 4;
	}
	*/
	return false;
}



