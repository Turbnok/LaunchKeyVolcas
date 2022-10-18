#include <MenuState.hpp>
#include <ConfigInOut.hpp>
#include <VolcaKeys.hpp>
#include <VolcaBass.hpp>
#include <midi.hpp>
#include <Volcas.hpp>
#include <Config.hpp>



bool
MenuState::receiveMidi(MidiMessage message){
	std::cout << "menu state midi message : " << message.channel << std::endl;
	if(message.data2.value() ==0) return false;
	if(message.data1.value() == LaunchKey::DrumPads::DP9){
		nextState = new VolcaKeys;
		return true;
	}
	if(message.data1.value() == LaunchKey::DrumPads::DP10){
		nextState = new VolcaBass;
		return true;
	}
	if(message.data1.value() == LaunchKey::DrumPads::DP16){
		nextState = new ConfigInOut;
		return true;
	}
	LaunchKey::DrumPads next;
	if(message.data1.value() == LaunchKey::DrumPads::DP1){
		//nextState = new VolcaKeys;
		Config::keyChannel = MidiChannel::CH1;	
		Config::setAsInt("KEYS_CHANNEL",static_cast<int>(Config::keyChannel));
		Config::setAsInt("KEYS_PAD",0);
		next =  LaunchKey::DrumPads::DP1;
	}
	if(message.data1.value() == LaunchKey::DrumPads::DP2){		
		Config::keyChannel = MidiChannel::CH2;
		Config::setAsInt("KEYS_CHANNEL",static_cast<int>(Config::keyChannel));
		Config::setAsInt("KEYS_PAD",1);
		next =  LaunchKey::DrumPads::DP2;
	}
	if(message.channel == MidiChannel::CH16 && (message.status == 176 || message.status ==  144)){
		return false;
	}	
	std::cout << "Menu state receive midi : " <<  message.channel <<  std::endl;

	MidiMessage resetMessage = LaunchKey::DrumPadColor;
	resetMessage.data1    =  currentPad;
    resetMessage.data2    =  Volcas::NONE;
    launchKey->SendMidiMessage(resetMessage);
	
	currentPad = next;
	MidiMessage colMessage = LaunchKey::DrumPadColorPulse;
	colMessage.data1    =  currentPad;
    colMessage.data2    =  Volcas::SELECT;
    launchKey->SendMidiMessage(colMessage);
	
	return false;
}


void
MenuState::gotoStep(int pStep){
	std::cout << "Menu state goto" << std::endl;
	currentPad = static_cast<LaunchKey::DrumPads>(LaunchKey::PADS[Config::getAsInt("KEYS_PAD")]);
	


	MidiMessage colMessage = LaunchKey::DrumPadColorPulse;
	colMessage.data1    =  currentPad;
    colMessage.data2    =  Volcas::SELECT;
    launchKey->SendMidiMessage(colMessage);
	
}
