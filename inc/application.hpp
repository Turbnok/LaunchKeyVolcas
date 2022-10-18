#pragma once

#include <midi.hpp>
#include <ScreenState.hpp>
#include <Screen.hpp>
#include <Sequencer.hpp>
#include <Config.hpp>



class Application
{
    private:
        Screen screen;
		
        int midiOutPort =   0;
        int midiInPort  =   0;
        int numColor    =   0;
        int mode = 0;
        int synth = 0;
        int menu = 0;

        std::shared_ptr<MidiOut>    midiOut =   nullptr;
        std::shared_ptr<MidiOut>    midiLaunch =   nullptr;
        std::shared_ptr<MidiIn>     midiPads  =   nullptr;
        std::shared_ptr<MidiIn>     midiKeys  =   nullptr;
        std::shared_ptr<MidiClock>     midiClock  =   nullptr;


        bool isPlaying = true;
        void timer_start(unsigned int interval);
        void do_something(void);

        void
        InitMIDI(void);

        void
        Touch(std::optional<MidiMessage> message);

        void
        MIDILoop(void);

        void
        Brightness(void);

    public:

        Application(){};
        ~Application(){};

        void
        Init(void);
        
        void
        initialState(int state);
        
        void
        Run(void);
};

