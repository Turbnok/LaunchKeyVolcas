#pragma once
#include <ScreenState.hpp>

class Screen
{
public:
    Screen();
    ~Screen(){};
    
    ScreenState* state;
    MidiOut* launchKey;
    MidiOut* out;
    MidiClock* midiClock;
    
    void setState(ScreenState* pState);
    void setMidiClock(MidiClock* midiIn);
    void setMidiOut(MidiOut* midiOut);
    void setLaunchKey(MidiOut* midiLaunch);
    void receiveMidi(MidiMessage message);
    
protected:
    void DoCleanUp();
    // Pointer which holds the current state
    // Since this is and base class pointer
    // of Concentrate classes, it can holds their objects
   
};
