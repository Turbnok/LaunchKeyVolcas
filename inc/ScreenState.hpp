#pragma once
#include <midi.hpp>
class ScreenState
{
	public:
		virtual bool receiveMidi(MidiMessage message);
		virtual ScreenState* getState();
		virtual void init(MidiOut* pLaunchKey,MidiOut* pOut);
		virtual void update();
	protected:
		MidiOut* launchKey;
		MidiOut* out;
		ScreenState* nextState;
};
