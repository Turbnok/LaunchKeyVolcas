#pragma once
#include <midi.hpp>
#include <chrono>
#include <ScreenState.hpp>
#include <Track.hpp>
#include <vector>
    

class Sequencer : public ScreenState
{
public:
    Sequencer();
    ~Sequencer();

    void update();
    bool receiveMidi(MidiMessage message);
    void receiveKeys(MidiMessage message);
    void init(MidiOut *pLaunchKey, MidiOut *pOut, MidiClock *midiClock);
    void show();
    void hide();
    void play();
    void stop();
    void record();
    void resume();

    void setRecord(bool onoff);
    void setTempo(int pTempo);

protected:
    Track tracks[16] = {};

    void showMenu();
    void hideMenu();
    void showPage(int page);
    void addMessage(MidiMessage message, int pStep);

    std::vector<MidiMessage> pressed;

    Modes mode = Modes::SESSION;
    bool playing = false;
    bool records = false;
    bool recording = false;
    int pads[16];
    int tempo = 80;
    int subdivisions = 8;
    int interval = 60000 / tempo / 4 / subdivisions;

    Track track = tracks[0];
    int currentStep = 0;
    int currentDivision = 0;
    int totalSteps = 16;

    int shift = false;
    std::chrono::steady_clock::time_point last = std::chrono::steady_clock::now();
};
