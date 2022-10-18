#pragma once

class Volcas
{
	public:
		static constexpr int KEYS_MAIN	= 105;
		static constexpr int BASS_MAIN	= 1;
		static constexpr int FM_MAIN	= 29;
		static constexpr int SAMPLE_MAIN= 72;
		static constexpr int DRUM_MAIN	= 9;
		static constexpr int KEYS_ALT	= 70;
		static constexpr int BASS_ALT	= 2;
		static constexpr int FM_ALT		= 30;
		static constexpr int SAMPLE_ALT	= 60;
		static constexpr int DRUM_ALT	= 10;
		static constexpr int NONE		= 0;
		static constexpr int SELECT		= 20;
};
class UI
{
	public:
		static constexpr int NONE		= 0;
		static constexpr int SELECT		= 20;
		static constexpr int IN			= 17;
		static constexpr int OUT		= 60;
};

class Pots{
	public:
		static constexpr int VCO		= 13;
		static constexpr int VCF		= 9;
		static constexpr int LFO		= 41;
		static constexpr int EG			= 49;
		static constexpr int OCT		= 5;		
		static constexpr int SPECIAL	= 57;		
		static constexpr int DELAY	= 25;		
		
	
};

class Keys
{
	public:
		static constexpr int PORTAMENTO		= 5;
		static constexpr int EXPRESSION		= 11;
		static constexpr int VOICE			= 40;
		static constexpr int OCTAVE			= 41;
		static constexpr int DETUNE			= 42;
		static constexpr int VCO_EG_IN		= 43;
		static constexpr int CUTOFF			= 44;
		static constexpr int VCF_EG_INT		= 45;
		static constexpr int LFO_RATE		= 46;
		static constexpr int LFO_PITCH_INT	= 47;
		static constexpr int LFO_CUTOFF_INT	= 48;
		static constexpr int EG_ATTACK		= 49;
		static constexpr int EG_DECAY_RELEASE	= 50;
		static constexpr int EG_SUSTAIN		= 51;
		static constexpr int DELAY_TIME		= 52;
		static constexpr int DELAY_FEEDBACK	= 53;
};

class Bass
{
	public:
		static constexpr int SLIDE_TIME	= 5;
		static constexpr int EXPRESSION	= 11;
		static constexpr int OCTAVE		= 40;
		static constexpr int LFO_RATE	= 41;
		static constexpr int LFO_INT	= 42;
		static constexpr int VCO_PITCH_1= 43;
		static constexpr int VCO_PITCH_2= 44;
		static constexpr int VCO_PITCH_3= 45; 
		static constexpr int EG_ATTACK	= 46;
		static constexpr int EG_DECAY_RELEASE= 47;
		static constexpr int CUTOFF_EG_INT= 48;
		static constexpr int GATE_TIME= 49;
};

