#pragma once
#include <midi.hpp>
#include <ScreenState.hpp>

class SequencerView : public ScreenState
{
public:
    SequencerView();
    SequencerView(unsigned int pcurrentTrack,unsigned int pcurrentSession);
    ~SequencerView();

    //void update();
    bool receiveMidi(MidiMessage message);
    void init(MidiOut *pLaunchKey, MidiOut *pOut, MidiClock *midiClock);
    void showPage(int pId);
    //Screens::Name getName();
    //void hide();
    void show();
protected:
    unsigned int currentTrack = 0;
    unsigned int currentSession = 0;
    unsigned int index = 0;
};
