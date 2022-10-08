#pragma once
#include "ScreenState.hpp"

class MenuState : public ScreenState
{
	public:
		MenuState();    
		~MenuState();
		// virtual ScreenState* back();
		// virtual ScreenState* GetNextState() = 0;
		virtual void init(MidiOut* pLaunchKey);
		virtual bool receiveMidi(MidiMessage message);
		//virtual    char* ToString();
};
