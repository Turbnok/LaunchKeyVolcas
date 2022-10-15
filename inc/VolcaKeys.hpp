#pragma once
#include <Volcas.hpp>
#include <Device.hpp>
#include <map>

class VolcaKeys : public Device
{
public:
        VolcaKeys(){};
        ~VolcaKeys(){};
        // bool receiveMidi(MidiMessage message);
        //  virtual ScreenState* back();
        //  virtual ScreenState* GetNextState() = 0;
        MidiChannel channel = MidiChannel::CH1;
        int currentStep = 0;
        // void init(MidiOut* pLaunchKey, MidiOut* pOut);

protected:
        int getCurrentStep() const { return currentStep; }
        MidiChannel getChannel() const { return channel; }
        const int *getMenuColors() const { return menuColors; }
        int menuColors[8] = {Pots::SPECIAL, Volcas::KEYS_MAIN, Volcas::KEYS_MAIN, 0, 0, 0, 0, 0};
        void step(int pStep);
        std::map<int, int> getMap()
        {
                if (getCurrentStep() == 0)
                {
                        return mapStep0;
                }
                else
                {
                        return mapStep1;
                }
        }
        std::map<int, int> mapStep0 = {
            {21, Keys::VOICE},
            {22, Keys::OCTAVE},
            {23, Keys::DETUNE},
            {24, Keys::PORTAMENTO},
            {25, Keys::VCO_EG_IN},
            {26, Keys::CUTOFF},
            {28, Keys::VCF_EG_INT}};
        std::map<int, int> mapStep1 = {
            {21, Keys::LFO_RATE},
            {22, Keys::LFO_PITCH_INT},
            {23, Keys::LFO_CUTOFF_INT},
            {24, Keys::EG_ATTACK},
            {25, Keys::EG_DECAY_RELEASE},
            {26, Keys::EG_SUSTAIN},
            {27, Keys::DELAY_TIME},
            {28, Keys::DELAY_FEEDBACK}};
};
