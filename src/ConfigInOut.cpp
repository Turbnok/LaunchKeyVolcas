#include <ConfigInOut.hpp>
#include <VolcaKeys.hpp>
#include <VolcaBass.hpp>
#include <MenuState.hpp>

#include <midi.hpp>
#include <Volcas.hpp>
#include <Config.hpp>
	
#include <vector>


bool
ConfigInOut::receiveMidi(MidiMessage message){
	std::cout << "menu state midi message : " << message.channel << std::endl;
	if(message.data2.value() ==0) return false;
	if(message.data1.value() == LaunchKey::DrumPads::DP9){
		nextState = new MenuState;
		return true;
	}
	LaunchKey::DrumPads next;
	int id = 0;
	for(std::vector<int>::iterator it = portsIn.begin(); it != portsIn.end(); ++it) {
		std::cout << *it << std::endl; 
  		LaunchKey::DrumPads pad = static_cast<LaunchKey::DrumPads>( LaunchKey::PADS[7-id++]);
		if(message.data1.value() == pad ){
			Config::setAsInt("MIDI_CLOCK_PORT",*it);
			
			midiClock->ClosePort();
			midiClock->OpenPort(*it,"LMV-Clock");
			next = pad;
			MidiMessage resetMessage = LaunchKey::DrumPadColor;
			resetMessage.data1    =  currentIn;
			resetMessage.data2    =  UI::IN;
			launchKey->SendMidiMessage(resetMessage);
			
			currentIn = next;
			MidiMessage colMessage = LaunchKey::DrumPadColorPulse;
			colMessage.data1    =  currentIn;
			colMessage.data2    =  UI::IN;
			launchKey->SendMidiMessage(colMessage);
			return false;
		}  
 	}
	id = 0;
	for(std::vector<int>::iterator it = portsOut.begin(); it != portsOut.end(); ++it) {
  		LaunchKey::DrumPads pad = static_cast<LaunchKey::DrumPads>( LaunchKey::PADS[15-id++]);
		
		if(message.data1.value() == pad){
			Config::setAsInt("MIDI_OUT_PORT",*it);
			out->ClosePort();
			out->OpenPort(*it,"LMV-Out");

			next = pad;
			MidiMessage resetMessage = LaunchKey::DrumPadColor;
			resetMessage.data1    =  currentOut;
			resetMessage.data2    =  UI::OUT;
			launchKey->SendMidiMessage(resetMessage);
			
			currentOut = next;
			MidiMessage colMessage = LaunchKey::DrumPadColorPulse;
			colMessage.data1    =  currentOut;
			colMessage.data2    =  UI::OUT;
			launchKey->SendMidiMessage(colMessage);
				return false;
		}  
 	}
	
	
	if(message.channel == MidiChannel::CH16 && (message.status == 176 || message.status ==  144)){
		return false;
	}	
	std::cout << "Menu state receive midi : " <<  message.channel <<  std::endl;

	
	
	return false;
}


void
ConfigInOut::gotoStep(int pStep){
	std::cout << "Menu state goto" << std::endl;
	unsigned int clockPort = Config::getAsInt("MIDI_CLOCK_PORT");
	unsigned int outPort = Config::getAsInt("MIDI_OUT_PORT");

	auto ports = out->GetPorts();
    MidiMessage outMessage = LaunchKey::DrumPadColor;
	
    for (unsigned int i = 0; i < ports.size(); ++i)
    {
		std::string en = ports.at(i);
		std::cout << "Port id: " << i << " name: " << ports.at(i) << std::endl;
		int ind = en.find("Launchkey Mini MK3");
		int ind2 = en.find("LMV-");		
        if(ind==-1 && ind2==-1){
			if(i==outPort){
				currentOut = static_cast<LaunchKey::DrumPads>(LaunchKey::PADS[15-portsOut.size()]);
			}
			outMessage.data1    =  LaunchKey::PADS[15-portsOut.size()];
	    	outMessage.data2    =  UI::OUT;
    		launchKey->SendMidiMessage(outMessage);
			portsOut.push_back(i);
		}
    }
	MidiMessage inMessage = LaunchKey::DrumPadColor;
	ports = midiClock->GetPorts();
	

    for (unsigned int i = 0; i < ports.size(); ++i)
    {
		std::cout << "Port id: " << i << " name: " << ports.at(i) << std::endl;
		std::string en = ports.at(i);
		int ind = en.find("Launchkey Mini MK3");
		int ind2 = en.find("LMV-");		
        if(ind==-1 && ind2==-1){
			if(i==clockPort){
				currentIn = static_cast<LaunchKey::DrumPads>(LaunchKey::PADS[15-portsIn.size()]);
			}
        	inMessage.data1    =  LaunchKey::PADS[7-portsIn.size()];
	    	inMessage.data2    =  UI::IN;
    		launchKey->SendMidiMessage(inMessage);
			portsIn.push_back(i);
		}
    }
	

	currentIn = static_cast<LaunchKey::DrumPads>(LaunchKey::PADS[7-clockPort]);
	currentOut = static_cast<LaunchKey::DrumPads>(LaunchKey::PADS[15-outPort]);
	
	MidiMessage colMessage = LaunchKey::DrumPadColorPulse;
	colMessage.data1    =  currentIn;
    colMessage.data2    =  UI::IN;
    launchKey->SendMidiMessage(colMessage);
	
	colMessage.data1    =  currentOut;
    colMessage.data2    =  UI::OUT;
    launchKey->SendMidiMessage(colMessage);
	
}
