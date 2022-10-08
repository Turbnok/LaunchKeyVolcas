#pragma once
#include <midi.hpp>
class ScreenState
{
	public:
		virtual bool receiveMidi(MidiMessage message);
		virtual ScreenState* getState();
		virtual void init(MidiOut* pLaunchKey);
	protected:
		MidiOut* launchKey;
		ScreenState* nextState;
		
};
