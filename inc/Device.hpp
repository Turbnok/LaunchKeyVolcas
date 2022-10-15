#pragma once
#include <ScreenState.hpp>
#include <Volcas.hpp>
#include <map>


class Device : public ScreenState
{
	public:
                Device(){};
		~Device(){};
		virtual bool receiveMidi(MidiMessage message);
		MidiChannel channel = MidiChannel::CH1;
		int currentStep = 0;

                virtual ScreenState* getState();
		void init(MidiOut* pLaunchKey,MidiOut* pOut);
		void gotoStep(int pInt);		
	protected:
                virtual int getCurrentStep() const { return currentStep; }
                virtual std::map<int,int> getMap(){ if(getCurrentStep()==0){
                                return mapStep0; 
                        }else {
                                return mapStep1; 
                        }}
                virtual MidiChannel getChannel() const { return channel; }
                const int* getMenuColors() const { return menuColors; }
                virtual void step(int stepId);
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
        };


