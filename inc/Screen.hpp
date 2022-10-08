#pragma once
#include <ScreenState.hpp>

class Screen
{
public:
    Screen();
    ~Screen(){};
    
    ScreenState* state;
    MidiOut* launchKey;
    void setState(ScreenState* pState);
    void setMidiOut(MidiOut* midiLaunch);
    void receiveMidi(MidiMessage message);
    
protected:
    void DoCleanUp();
    // Pointer which holds the current state
    // Since this is and base class pointer
    // of Concentrate classes, it can holds their objects
   
};
