#pragma once
#include <ScreenState.hpp>
#include <Volcas.hpp>

class MenuState : public ScreenState
{
	public:
		MenuState(){};
		~MenuState(){};
		bool receiveMidi(MidiMessage message);
	protected:
		virtual const int* getMenuColors() const { return menuColors; }
		int menuColors[8] = {Volcas::KEYS_MAIN,Volcas::BASS_MAIN,Volcas::FM_MAIN,Volcas::SAMPLE_MAIN,Volcas::DRUM_MAIN};
};
