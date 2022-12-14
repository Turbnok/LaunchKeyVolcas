#pragma once
#include <midi.hpp>

namespace Screens
{
	enum Name{
		Menu,
		Session,
		SequencerView		
	};
}

class ScreenState
{
	public:
		ScreenState(){};
		~ScreenState(){};
		virtual void show();
		virtual void hide();
		virtual bool receiveMidi(MidiMessage message);
		virtual ScreenState* getState();
		virtual Screens::Name getName();
		void init(MidiOut* pLaunchKey,MidiOut* pOut, MidiClock* pClock); 
		virtual void gotoStep(int pInt);
	protected:
		MidiOut* launchKey;
		MidiOut* out;
		MidiClock* midiClock;
		ScreenState* nextState;
		int currentStep = 0;
		bool shown = false;

		int menuColors[8] = {0,0,0,0,0,0,0,0};
		virtual const int* getMenuColors() const { return menuColors; }
		virtual void step(int stepId);
};
