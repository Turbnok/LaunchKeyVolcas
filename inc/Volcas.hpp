#pragma once

class Volcas
{
	public:
		static constexpr int KEYS_MAIN	= 105;
		static constexpr int BASS_MAIN	= 1;
		static constexpr int FM_MAIN	= 29;
		static constexpr int SAMPLE_MAIN	= 72;
		static constexpr int DRUM_MAIN	= 9;
		static constexpr int KEYS_ALT	= 70;
		static constexpr int BASS_ALT	= 2;
		static constexpr int FM_ALT		= 30;
		static constexpr int SAMPLE_ALT	= 60;
		static constexpr int DRUM_ALT	= 10;
		static constexpr int NONE		= 0;
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
/*
enum Bass
{
	PORTAMENTO	= 5;
	EXPRESSION	= 11;
	OCTAVE		= 40;
	LFO_RATE;
	LFO_INT;
	VCO_PITCH_1; 
	VCO_PITCH_2;
	VCO_PITCH_3; 
	EG_ATTACK;
	EG_DECAY_RELEASE;
	CUTOFF_EG_INT;
	GATE_TIME;
};*/
