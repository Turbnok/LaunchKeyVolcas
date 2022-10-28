#pragma once
#include <midi.hpp>
#include <chrono>
#include <ScreenState.hpp>
#include <Track.hpp>
#include <Volcas.hpp>
#include <vector>

class Session : public ScreenState
{
public:
    Session();
    ~Session();

    //void update();
    bool receiveMidi(MidiMessage message);
    void init(MidiOut *pLaunchKey, MidiOut *pOut, MidiClock *midiClock);
    void showPage(int pId);
    //void hide();
    void show();
protected:
    unsigned int index = 0;
    unsigned int nbDevices = 5;
    unsigned int devices[5];
    unsigned int devicesColors[5] =  {Volcas::KEYS_MAIN,Volcas::BASS_MAIN,Volcas::FM_MAIN,Volcas::SAMPLE_MAIN,Volcas::DRUM_MAIN};

};
