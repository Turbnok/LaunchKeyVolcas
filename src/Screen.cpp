
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
Screen::setLaunchKey(MidiOut* midiLaunch){
	launchKey = midiLaunch;	
}
void
Screen::setState(ScreenState* pState)
{	
	std::cout << "setState" << std::endl;
	state = pState;
	state->init(launchKey, out);
	
    /*
		MidiMessage colMessage = LaunchKey::DrumPadColor;
		m_pState->receiveMidi(colMessage);
    */
}
void
Screen::update(){
	state->update();
}
void
Screen::receiveMidi(MidiMessage message){
	std::cout << "screen reveive midi" << std::endl;
	// global message
	
	if(CompareMidiMessage(message,LaunchKey::Play)){
		
		MidiMessage playMessage{};
		playMessage.channel = MidiChannel::CH1;
		playMessage.status = MidiStatus::START; 
		playMessage.data2    = 0;
		playMessage.data1    = 0x01;
		out->SendMidiMessage(playMessage);
		
		MidiMessage messagePlay = LaunchKey::Play;
		messagePlay.channel = MidiChannel::CH2;
		messagePlay.data2 = 0x01;
		launchKey->SendMidiMessage(messagePlay);
	}	
	
	if(CompareMidiMessage(message,LaunchKey::Record)){
	
		MidiMessage stopMessage{};
		stopMessage.channel = MidiChannel::CH1;
		stopMessage.status = MidiStatus::STOP; 
		stopMessage.data2    = 0;
		stopMessage.data1    = 1;
		out->SendMidiMessage(stopMessage);
	
		MidiMessage messageStop = LaunchKey::Play;
		messageStop.channel = MidiChannel::CH2;
		messageStop.data2 = 0x00;
		launchKey->SendMidiMessage(messageStop);
	
	}	
	
	bool hasToChange = state->receiveMidi(message);
	if(hasToChange){
		ScreenState* newState = state->getState();
		newState->init(launchKey, out);		
		state = newState;
	}
}
