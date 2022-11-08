#pragma once
#include <midi.hpp>
#include <Sequence.hpp>
#include <vector>


class Track
{
	public:
		Track(){
			sequences.push_back(new Sequence);
			sequence = sequences.at(0);
		};    
		~Track(){};
        int8_t selected = 0;	
		int8_t chains[16];
		Sequence* sequence;
        
	protected:
        std::vector<Sequence*> sequences;
};

