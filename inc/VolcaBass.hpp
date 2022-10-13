#pragma once
#include <ScreenState.hpp>
#include <Volcas.hpp>
#include <map>


class VolcaBass : public ScreenState
{
public:
        VolcaBass();
        ~VolcaBass();
        // virtual ScreenState* back();
        // virtual ScreenState* GetNextState() = 0;
        MidiChannel channel = MidiChannel::CH2;
        int currentStep = 0;
        void init(MidiOut *pLaunchKey, MidiOut *pOut);
        bool receiveMidi(MidiMessage message);

protected:
        std::map<int, int> mapStep0 = {
            {21, Bass::OCTAVE},
			{22, Bass::VCO_PITCH_1},
			{23, Bass::VCO_PITCH_2},
            {24, Bass::VCO_PITCH_3},
            {25, Bass::LFO_RATE},
            {26, Bass::LFO_INT},
        };
        std::map<int, int> mapStep1 = {
            {21, Bass::EG_ATTACK},
            {22, Bass::EG_DECAY_RELEASE},
            {23, Bass::CUTOFF_EG_INT},
            {26, Bass::EXPRESSION},
            {27, Bass::GATE_TIME},
            {28, Keys::DELAY_FEEDBACK}};
        void step(int pStep);
};
