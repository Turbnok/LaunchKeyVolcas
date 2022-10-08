


//#include "MenuState.hpp"
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
Screen::setMidiOut(MidiOut* midiLaunch){
	launchKey = midiLaunch;	
}
void
Screen::setState(ScreenState* pState)
{	
	std::cout << "setState" << std::endl;
	state = pState;
	state->init(launchKey);
	
    /*
		MidiMessage colMessage = LaunchKey::DrumPadColor;
		m_pState->receiveMidi(colMessage);
    */
}
void
Screen::receiveMidi(MidiMessage message){
	std::cout << "screen reveive midi" << std::endl;
	bool hasToChange = state->receiveMidi(message);
	if(hasToChange){
		ScreenState* newState = state->getState();
		newState->init(launchKey);		
		state = newState;
	}
}
