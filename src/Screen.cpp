
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
		record = !record;
		sequencer->setRecord(record);
		MidiMessage recordMessage =  LaunchKey::Record;//LaunchKey::DrumPadColor;
		if(!record){
			recordMessage.data2 = 0;
		}		
		//recordMessage.data1    = LaunchKey::Record;
		//recordMessage.data2    = record ? 127 : 0;
		out->SendMidiMessage(recordMessage);
		/*
		MidiMessage messageStop = LaunchKey::Play;
		messageStop.channel = MidiChannel::CH1;
		messageStop.data2 = 0x00;
		launchKey->SendMidiMessage(messageStop);	
		*/
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
	bool hasToChange = state->receiveMidi(message);
	if(hasToChange){
		ScreenState* newState = state->getState();
		newState->init(launchKey, out, midiClock);		
		newState->gotoStep(0);
		state = newState;
	}
}
