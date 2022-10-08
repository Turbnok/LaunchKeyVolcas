#pragma once
#include "ScreenState.hpp"

class KeysState : public ScreenState
{
	public:
		KeysState();    
		~KeysState();
		// virtual ScreenState* back();
		// virtual ScreenState* GetNextState() = 0;
		void init(MidiOut* pLaunchKey);
		bool receiveMidi(MidiMessage message);
		//virtual    char* ToString();
};
