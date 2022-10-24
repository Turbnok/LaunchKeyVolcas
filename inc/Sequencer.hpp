#pragma once
#include <midi.hpp>
#include <chrono>
#include <ScreenState.hpp>
#include <vector>




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
        void record();
        void resume();

        void setRecord(bool onoff);
        void setTempo(int pTempo);
	protected:
        
        void showPage(int page);
        void addMessage(MidiMessage message, int pStep);
        
        std::vector<MidiMessage> pressed;
        std::vector<MidiMessage> motion[64];
        bool keysOn[64] = {false};
        bool keysMute[64] = {false};
        bool shown = false;
        bool playing = false;

        bool records = false;
        bool recording = false;
        int pads[16];
        int tempo = 80;
        int subdivisions = 4;        
        int interval = 60000 / tempo / 4 / subdivisions;
		int currentStep = 0;
        int currentDivision = 0;
        int totalSteps = 16;

        std::vector<MidiMessage> msg[64 * 4]; // subdivisions
        std::chrono::steady_clock::time_point last = std::chrono::steady_clock::now();
};

