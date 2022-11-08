
#include <Screen.hpp>
#include <ScreenState.hpp>
#include <Session.hpp>
#include <midi.hpp>


Screen::Screen()
{
	session = new Session;
	
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
	session->init(launchKey, out, midiClock);	
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
	std::cout << "screen reveive midi" <<message.status<<std::endl;
	
	// global message
	// ignore pitch or modulation	
    if (message.status == 224) 
    {
		return;
	}
	sequencer->receiveMidi(message);
	
	
	
	bool hasToChange = state->receiveMidi(message);
	if(hasToChange){
		ScreenState* newState = state->getState();
		if(newState->getName() == Screens::SequencerView){
			// Session * ses = dynamic_cast<Session*>(state);
			
			// std::cout << ses->currentSession << std::endl;
			// std::cout << ses->currentTrack << std::endl;
			
			//newState->setSequencer(sequencer);
		}
		newState->init(launchKey, out, midiClock);		
		newState->gotoStep(0);
		state = newState;
	}
}
