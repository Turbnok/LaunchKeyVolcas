#pragma once
#include <ScreenState.hpp>
#include <midi.hpp>
#include <chrono>


class Sequencer: public ScreenState
{
	public:
		Sequencer();    
		~Sequencer();		
		
        void update();
        bool receiveMidi(MidiMessage message);
        void init(MidiOut *pLaunchKey, MidiOut *pOut);
        void play();
        void stop();
        void resume();
        void setTempo(int pTempo);
	protected:
        int pads[16];
        int tempo = 120;
        int interval = 60000 / tempo / 4;
		int currentStep = 0;
        int subdivisions = 4;        
        int totalSteps = 16;

        std::chrono::steady_clock::time_point last = std::chrono::steady_clock::now();
};

