#pragma once
#include <ScreenState.hpp>
#include <Sequencer.hpp>
#include <Session.hpp>

class Screen
{
public:
    Screen();
    ~Screen(){};
    
    ScreenState* state;
    ScreenState* oldState;
    

    MidiOut* launchKey;
    MidiOut* out;
    MidiClock* midiClock;
    Sequencer* sequencer;
    Session* session;
        
    void setState(ScreenState* pState);
    void setMidiClock(MidiClock* midiIn);
    void setMidiOut(MidiOut* midiOut);
    void setSequencer(Sequencer* sequencer);
    void setLaunchKey(MidiOut* midiLaunch);
    void receiveMidi(MidiMessage message);
    
protected:
    bool mode = false;
    bool record = false;
};

