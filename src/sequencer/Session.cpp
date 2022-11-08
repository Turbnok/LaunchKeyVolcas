#include <Session.hpp>
#include <MenuState.hpp>
#include <SequencerView.hpp>
#include <map>
Session::Session()
{

}
Session::~Session()
{

}
void
Session::showPage(int pId){
    MidiMessage colMessage = LaunchKey::DrumPadColor;
    for (int i = 0; i < 16; i++)
	{
        if(i!=0 && i!=8){
			LaunchKey::DrumPads pad = static_cast<LaunchKey::DrumPads>(LaunchKey::PADS[i]);
			colMessage.data1 = pad;
			colMessage.data2 = 0;
			launchKey->SendMidiMessage(colMessage);
        }
	}

    for (int j = 0; j < 2; j++)
	{

    LaunchKey::DrumPads pad = static_cast<LaunchKey::DrumPads>(LaunchKey::PADS[j*8]);
	colMessage.data1 = pad;
	colMessage.data2 = devicesColors[pId+j];
	launchKey->SendMidiMessage(colMessage);
    
    }
}


void Session::init(MidiOut *pLaunchKey, MidiOut *pOut, MidiClock *pClock)
{
	std::cout << "Sequence Init" << std::endl;
	// ScreenState::init(pLaunchKey,pOut,pClock);
	out = pOut;
	midiClock = pClock;
	launchKey = pLaunchKey;
}
void Session::show()
{
	std::cout << "sequencer show" << std::endl;
	showPage(0);
}

bool Session::receiveMidi(MidiMessage message)
{
	std::cout << "Sequencer receive midi : " << message.data1.value() <<":"<< message.data2.value() << std::endl;
    if(CompareMidiMessage(message,LaunchKey::ArrUp)){
		if(currentSession!=UINT_MAX && currentTrack!=UINT_MAX){
			nextState = new SequencerView(currentSession,currentTrack);
		}else{
			nextState = new MenuState;
		}
		return true;
	}
	if(message.data1.value() == LaunchKey::Knob::K1){
        unsigned int val = ((message.data2.value()) / (128/(nbDevices-1)));
        if( val != index){
            index = val;
            std::cout << "index : " << index << std::endl;
            showPage(index);
        }
    }
	LaunchKey::DrumPads pad = static_cast<LaunchKey::DrumPads>(message.data1.value());
	std::map<int,int>::const_iterator it = LaunchKey::PadsId.find(pad);
	
	if(it != LaunchKey::PadsId.end() && message.data2.value()>0){
		//press
		currentSession = it->second % 8;
		currentTrack = index +  it->second/8;
	}else if(it != LaunchKey::PadsId.end() && message.data2.value()==0){
		//release		
		currentTrack = UINT_MAX;
		currentSession = UINT_MAX;
		std::cout<<"currentTrack" << currentTrack <<std::endl;
		std::cout<<"current Session " << currentSession <<std::endl;

	}
	return false;
}

