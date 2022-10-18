#pragma once
#include <ScreenState.hpp>
#include <Volcas.hpp>
#include <vector>

class ConfigInOut : public ScreenState
{
	public:
		ConfigInOut(){};
		~ConfigInOut(){};
		LaunchKey::DrumPads currentIn = LaunchKey::DrumPads::DP1;
		LaunchKey::DrumPads currentOut = LaunchKey::DrumPads::DP2;
		
		std::vector<int> portsIn;
		std::vector<int> portsOut;
		
		bool receiveMidi(MidiMessage message);
		void gotoStep(int pStep);
	protected:
		virtual const int* getMenuColors() const { return menuColors; }
		int menuColors[8] = {Pots::SPECIAL,0,0,0,0,0,0,0};
};
