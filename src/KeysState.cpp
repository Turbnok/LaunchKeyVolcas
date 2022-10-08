#include <KeysState.hpp>
#include <MenuState.hpp>

KeysState::KeysState(){
	std::cout << "KeysState Constructor" << std::endl;
}
KeysState::~KeysState(){
	std::cout << "KeysState deconstructor" << std::endl;
}
void 
KeysState::init(MidiOut* pLaunchKey){
	std::cout << "KeysState Init" << std::endl;	
	ScreenState::init(pLaunchKey);
	
	
	
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
	int colors[4] = {18,18,18,18};
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
KeysState::receiveMidi(MidiMessage message){
	std::cout << "KeysState midi message" << message.channel << std::endl;
	if(message.data2.value()!=0){
		nextState = new MenuState;
		return true;
	}
	return false;
}

