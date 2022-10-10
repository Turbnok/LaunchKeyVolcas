#include <MenuState.hpp>
#include <KeysState.hpp>
#include <BassState.hpp>
#include <midi.hpp>
#include <Volcas.hpp>

MenuState::MenuState(){
	std::cout << "constructor" << std::endl;
}
MenuState::~MenuState(){
	std::cout << "deconstructor" << std::endl;
}
void 
MenuState::init(MidiOut* pLaunchKey,MidiOut* pOut){
	ScreenState::init(pLaunchKey,pOut);
	
	std::cout << "Init Menu State" << std::endl;	
	
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
	int colors[4] = {Volcas::KEYS_MAIN,Volcas::BASS_MAIN,Volcas::FM_MAIN,Volcas::SAMPLE_MAIN};
    for (int i = 0; i < 4; ++i)
       {
			colMessage.data2   =   colors[i];
			colMessage.data1   =   LaunchKey::DrumPads::DP9 + i;
            launchKey->SendMidiMessage(colMessage);
    }
    colors[0] = Volcas::DRUM_MAIN;
    colors[1] = colors[2] = colors[3] = 0;
    
	for (int i = 0; i < 4; ++i)
	{
		colMessage.data2   =   colors[i];
		colMessage.data1   =   LaunchKey::DrumPads::DP13 + i;
		launchKey->SendMidiMessage(colMessage);
	}
	
}
bool
MenuState::receiveMidi(MidiMessage message){
	std::cout << "menu state midi message : " << message.channel << std::endl;
	std::cout << " : " << message.data1.value() << std::endl;
	if(message.data1.value()== LaunchKey::DrumPads::DP9){
		nextState = new KeysState;
		return true;
	}
	if(message.data1.value()== LaunchKey::DrumPads::DP10){
		nextState = new BassState;
		return true;
	}
	return false;
}



