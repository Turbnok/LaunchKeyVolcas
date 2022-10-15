#pragma once
#include <midi.hpp>
class ScreenState
{
	public:
		ScreenState(){};
		~ScreenState(){};
		virtual bool receiveMidi(MidiMessage message);
		virtual ScreenState* getState();
		void init(MidiOut* pLaunchKey,MidiOut* pOut);
		void gotoStep(int pInt);
	protected:
		MidiOut* launchKey;
		MidiOut* out;
		ScreenState* nextState;

		int menuColors[8] = {0,0,12,0,0,0,0,0};
		virtual const int* getMenuColors() const { return menuColors; }
		virtual void step(int stepId);
};
