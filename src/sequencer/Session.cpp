#include <Session.hpp>

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
	if(message.data1.value() == 21){
        // knob 1
        unsigned int val = ((message.data2.value()) / (128/(nbDevices-1)));
        if( val != index){
            index = val;
            std::cout << "index : " << index << std::endl;
            showPage(index);
        }
    }
	return false;
}

