#include <MenuState.hpp>
#include <VolcaKeys.hpp>
#include <VolcaBass.hpp>
#include <midi.hpp>
#include <Volcas.hpp>


bool
MenuState::receiveMidi(MidiMessage message){
	std::cout << "menu state midi message : " << message.channel << std::endl;
	std::cout << " : " << message.data1.value() << std::endl;
	if(message.data2.value() ==0) return false;
	if(message.data1.value() == LaunchKey::DrumPads::DP9){
		nextState = new VolcaKeys;
		return true;
	}
	if(message.data1.value() == LaunchKey::DrumPads::DP10){
		nextState = new VolcaBass;
		return true;
	}
	return false;
}



