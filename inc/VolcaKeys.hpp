#pragma once
#include <ScreenState.hpp>
#include <Volcas.hpp>
#include <map>

class VolcaKeys : public ScreenState
{
	public:
		VolcaKeys();    
		~VolcaKeys();		
		// virtual ScreenState* back();
		// virtual ScreenState* GetNextState() = 0;
		MidiChannel channel = MidiChannel::CH1;
		int currentStep = 0;
		void init(MidiOut* pLaunchKey, MidiOut* pOut);
		bool receiveMidi(MidiMessage message);
		
	protected:
		std::map<int,int> mapStep0 = {
                { 21, Keys::VOICE },
                { 22, Keys::OCTAVE },
                { 23, Keys::DETUNE },
                { 24, Keys::PORTAMENTO },
                { 25, Keys::VCO_EG_IN },
                { 26, Keys::CUTOFF },
                { 28, Keys::VCF_EG_INT }
               }; 
		std::map<int,int> mapStep1 = {
                { 21, Keys::LFO_RATE },
                { 22, Keys::LFO_PITCH_INT },
                { 23, Keys::LFO_CUTOFF_INT },
                { 24, Keys::EG_ATTACK },
                { 25, Keys::EG_DECAY_RELEASE },
                { 26, Keys::EG_SUSTAIN },
                { 27, Keys::DELAY_TIME },
                { 28, Keys::DELAY_FEEDBACK }
               }; 
	void step(int pStep);
};

