#pragma once
#include <midi.hpp>
class ScreenState
{
	public:
		virtual bool receiveMidi(MidiMessage message);
		virtual ScreenState* getState();
		virtual void init(MidiOut* pLaunchKey,MidiOut* pOut);
	protected:
		MidiOut* launchKey;
		MidiOut* out;
		ScreenState* nextState;
		
};
