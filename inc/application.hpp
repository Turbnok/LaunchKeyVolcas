#pragma once

#include "midi.hpp"

class Application
{
    private:

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
        bool isPlaying = true;

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
