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
    
    void setState(ScreenState* pState);
    void setMidiOut(MidiOut* midiOut);
    void setLaunchKey(MidiOut* midiLaunch);
    void receiveMidi(MidiMessage message);
    
protected:
    void DoCleanUp();
    // Pointer which holds the current state
    // Since this is and base class pointer
    // of Concentrate classes, it can holds their objects
   
};
