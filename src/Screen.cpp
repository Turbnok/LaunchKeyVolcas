
#include <Screen.hpp>
#include <ScreenState.hpp>
#include <midi.hpp>



Screen::Screen()
{
	
    /*
		MidiMessage colMessage = LaunchKey::DrumPadColor;
		m_pState->receiveMidi(colMessage);
    */
}
void 
Screen::setMidiOut(MidiOut* midiOut){
	out = midiOut;	
}
void 
Screen::setMidiClock(MidiClock* midiIn){
	midiClock = midiIn;	
}
void
Screen::setLaunchKey(MidiOut* midiLaunch){
	launchKey = midiLaunch;	
}
void
Screen::setSequencer(Sequencer* pSequencer){
	sequencer = pSequencer;
	sequencer->init(launchKey, out, midiClock);
}
void
Screen::setState(ScreenState* pState)
{	
	std::cout << "setState" << std::endl;
	state = pState;
	state->init(launchKey, out, midiClock);
	state->gotoStep(0);
	
    /*
		MidiMessage colMessage = LaunchKey::DrumPadColor;
		m_pState->receiveMidi(colMessage);
    */
}

void
Screen::receiveMidi(MidiMessage message){
	std::cout << "screen reveive midi" << std::endl;
	// global message
	  // ignore pitch or modulation
    if (message.status == 224 || (message.status == 176 && message.data2 == 0)) 
    {
		
		return;
	}
	if(CompareMidiMessage(message,LaunchKey::ArrUp)){
		mode = !mode;
		state->hide();
		if(mode){
			oldState = state;
			state = sequencer;
		}else{
			state = oldState;
		}		
		state->show();
		return;
	}
	if(!mode){
		// sends midi even if sequencer is not shown (for play/record)
		sequencer->receiveMidi(message);
	}
	bool hasToChange = state->receiveMidi(message);
	if(hasToChange){
		ScreenState* newState = state->getState();
		newState->init(launchKey, out, midiClock);		
		newState->gotoStep(0);
		state = newState;
	}
}
