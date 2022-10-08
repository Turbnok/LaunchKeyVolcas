#include <MenuState.hpp>
#include <KeysState.hpp>
#include <midi.hpp>

MenuState::MenuState(){
	std::cout << "constructor" << std::endl;
}
MenuState::~MenuState(){
	std::cout << "deconstructor" << std::endl;
}
void 
MenuState::init(MidiOut* pLaunchKey){
	ScreenState::init(pLaunchKey);
	
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
	int colors[4] = {9,9,9,9};
    for (int i = 0; i < 4; ++i)
       {
		colMessage.data2   =   colors[i];
           colMessage.data1   =   LaunchKey::DrumPads::DP9 + i;
            launchKey->SendMidiMessage(colMessage);
    }
	for (int i = 0; i < 4; ++i)
	{
		colMessage.data1   =   LaunchKey::DrumPads::DP13 + i;
		launchKey->SendMidiMessage(colMessage);
	}
	
}
bool
MenuState::receiveMidi(MidiMessage message){
	std::cout << "menu state midi message" << message.channel << std::endl;
	
	if(message.data2.value()!=0){
		nextState = new KeysState;
		return true;
	}
	return false;
}


