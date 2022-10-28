#include <Sequence.hpp>
Sequence::Sequence()
{

}
Sequence::~Sequence()
{

}
void
Sequence::clear(){	
	for (auto& v : msg) {
   	 	v.clear();
	}	
    std::fill(std::begin(keysOn), std::end(keysOn), 0);
}
void
Sequence::addMessage(MidiMessage message, int pStep){	
	msg[pStep].push_back(message);
    
}
