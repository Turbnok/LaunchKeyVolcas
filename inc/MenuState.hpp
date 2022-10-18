#pragma once
#include <ScreenState.hpp>
#include <Volcas.hpp>
//#include <Pots.hpp>

class MenuState : public ScreenState
{
	public:
		MenuState(){};
		~MenuState(){};
		LaunchKey::DrumPads currentPad = LaunchKey::DrumPads::DP1;
		bool receiveMidi(MidiMessage message);
		void gotoStep(int pStep);
	protected:
		virtual const int* getMenuColors() const { return menuColors; }
		int menuColors[8] = {Volcas::KEYS_MAIN,Volcas::BASS_MAIN,Volcas::FM_MAIN,Volcas::SAMPLE_MAIN,Volcas::DRUM_MAIN,0,0,Pots::SPECIAL};
};
