#pragma once
#include <midi.hpp>
#include <vector>


class Sequence
{
	public:
		Sequence();    
		~Sequence();
                void clear();
                void setBars();
                void setColor();
                bool keysOn[64] = {false};
                void addMessage(MidiMessage message, int pStep);
                std::vector<MidiMessage> msg[64 * 8]; // subdivisions
                
	protected:
                // std::vector<MidiMessage> motion[64];
               // bool keysMute[64] = {false};
};

