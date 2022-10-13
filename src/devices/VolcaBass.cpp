#include <VolcaBass.hpp>
#include <MenuState.hpp>
#include <Volcas.hpp>
#include <Sequencer.hpp>
#include <map>

VolcaBass::VolcaBass(){
	std::cout << "VolcaBass Constructor" << std::endl;
}
VolcaBass::~VolcaBass(){
	std::cout << "VolcaBass deconstructor" << std::endl;
}
void 
VolcaBass::init(MidiOut* pLaunchKey, MidiOut* pOut){
	std::cout << "VolcaBass Init" << std::endl;    
	ScreenState::init(pLaunchKey,pOut);		
	MidiMessage colMessage = LaunchKey::DrumPadColor;
    colMessage.data2   =   0;
	for (int i = 0; i < 4; ++i)
	{
		colMessage.data1   =   LaunchKey::DrumPads::DP1 + i;
		launchKey->SendMidiMessage(colMessage);
	}
	for (int i = 0; i < 4; ++i)
	{
		colMessage.data1   =   LaunchKey::DrumPads::DP5 + i;
		launchKey->SendMidiMessage(colMessage);
	}
	int colors[4] = {Volcas::BASS_MAIN,Volcas::BASS_MAIN,0,0};
    for (int i = 0; i < 4; ++i)
    {
		colMessage.data2   =   colors[i];
        colMessage.data1   =   LaunchKey::DrumPads::DP9 + i;
        launchKey->SendMidiMessage(colMessage);
    }
    colMessage.data2   =   0;
	for (int i = 0; i < 4; ++i)
	{
		colMessage.data1   =   LaunchKey::DrumPads::DP13 + i;
		launchKey->SendMidiMessage(colMessage);
	}
	step(0);	
}
void
VolcaBass::step(int pStep){
	//
	MidiMessage resetMessage = LaunchKey::DrumPadColor;
	resetMessage.data1    =  LaunchKey::DrumPads::DP9 + currentStep;
    resetMessage.data2    =  Volcas::BASS_MAIN;
    launchKey->SendMidiMessage(resetMessage);
	
	currentStep = pStep;
	MidiMessage colMessage = LaunchKey::DrumPadColorFlash;
	colMessage.data1    =    LaunchKey::DrumPads::DP9 + pStep;
    colMessage.data2    =  Volcas::BASS_ALT;
    launchKey->SendMidiMessage(colMessage);
    
    if(pStep == 0){
		colMessage = LaunchKey::DrumPadColor;
		int colors[4] = {Pots::OCT,Pots::VCO,Pots::VCO,Pots::VCO};
		for (int i = 0; i < 4; ++i)
		{
			colMessage.data1   =   LaunchKey::DrumPads::DP1 + i;
			colMessage.data2   = colors[i] ;
			launchKey->SendMidiMessage(colMessage);
		}
		colors[0] = Pots::LFO;
		colors[1] = Pots::LFO;
		colors[2] = 0;
		colors[3] = 0;
		for (int i = 0; i <	4; ++i)
		{
			colMessage.data1   = LaunchKey::DrumPads::DP5 + i;
			colMessage.data2   = colors[i] ;
			launchKey->SendMidiMessage(colMessage);
		}
	}else if(pStep == 1){
	
		colMessage = LaunchKey::DrumPadColor;
		int colors[4] = {Pots::EG,Pots::EG,Pots::EG,0};
		for (int i = 0; i < 4; ++i)
		{
			colMessage.data1   =   LaunchKey::DrumPads::DP1 + i;
			colMessage.data2   = colors[i] ;
			launchKey->SendMidiMessage(colMessage);
		}
		colors[0] = 0;
		colors[1] = Pots::SPECIAL;
		colors[2] = Pots::SPECIAL;
		colors[3] = Pots::SPECIAL;
		
		for (int i = 0; i <	4; ++i)
		{
			colMessage.data1   = LaunchKey::DrumPads::DP5 + i;
			colMessage.data2   = colors[i] ;
			launchKey->SendMidiMessage(colMessage);
		}
	}
    //
    
	
}
bool
VolcaBass::receiveMidi(MidiMessage message){
	std::cout << "VolcaBass midi message" << message.channel << std::endl;
	// back
	if(CompareMidiMessage(message,LaunchKey::ArrDown)){
		nextState = new MenuState;
		return true;
	}
	if(CompareMidiMessage(message,LaunchKey::ArrUp)){
		nextState = new Sequencer;
		return true;
	}
	
	
	if(message.channel == 15){
		// pots
		MidiMessage sendMessage = LaunchKey::DrumPadColor;
		sendMessage.channel = channel;
		sendMessage.status = MidiStatus::CC; 
		sendMessage.data2    =  message.data2.value();
		if(currentStep == 0){		
			if(mapStep0.count(message.data1.value())>0){
				sendMessage.data1 = mapStep0.at( message.data1.value() );
				out->SendMidiMessage(sendMessage);
			}
		}else if(currentStep == 1){
			if(mapStep1.count(message.data1.value())>0){
				sendMessage.data1 = mapStep1.at( message.data1.value() );
				out->SendMidiMessage(sendMessage);
			}
		}
		
	}	
	if(message.data2.value() ==0) return false;
	if(message.data1.value() == LaunchKey::DrumPads::DP9){
		step(0);		
	} 
	if(message.data1.value() == LaunchKey::DrumPads::DP10){
		step(1);		
	}
	if(message.data1.value() == LaunchKey::DrumPads::DP11){
		std::cout << "P111" << message.channel << std::endl;
		MidiMessage playMessage = LaunchKey::DrumPadColor;
		playMessage.channel = MidiChannel::CH1;
		playMessage.status = MidiStatus::START; 
		playMessage.data2    = 0;
		playMessage.data1    = 0x1;
		out->SendMidiMessage(playMessage);
		return false;
	}
	return false;
}


