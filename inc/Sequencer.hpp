#pragma once
#include <midi.hpp>
#include <chrono>
#include <ScreenState.hpp>




class Sequencer : public ScreenState
{
	public:
		Sequencer();    
		~Sequencer();		
		
        void update();
        bool receiveMidi(MidiMessage message);
        void receiveKeys(MidiMessage message);
        void init(MidiOut* pLaunchKey, MidiOut* pOut, MidiClock* midiClock);
        void show();
        void hide();
        void play();
        void stop();
        void resume();
        void setRecord(bool onoff);
        void setTempo(int pTempo);
	protected:
        MidiMessage msg[16][10]{};
        bool shown = false;
        bool record = false;
        int pads[16];
        int tempo = 120;
        int interval = 60000 / tempo / 4;
		int currentStep = 0;
        int subdivisions = 4;        
        int totalSteps = 16;

        std::chrono::steady_clock::time_point last = std::chrono::steady_clock::now();
};

