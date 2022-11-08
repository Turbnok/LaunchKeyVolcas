#include <SequencerView.hpp>

SequencerView::SequencerView(unsigned int pcurrentTrack,unsigned int pcurrentSession)
{
	std::cout << "SequencerView constructor" << std::endl;
  currentTrack = pcurrentTrack;
  currentSession = pcurrentSession;
  std::cout << "currentTrack"<<currentTrack << std::endl;
  std::cout << "currentSession"<<currentSession << std::endl;
}

SequencerView::SequencerView()
{
	std::cout << "SequencerView constructor" << std::endl;

}
SequencerView::~SequencerView()
{
	std::cout << "deconstructor" << std::endl;
}

void
SequencerView::showPage(int pId){

}


void SequencerView::init(MidiOut *pLaunchKey, MidiOut *pOut, MidiClock *pClock)
{
	
	out = pOut;
	midiClock = pClock;
	launchKey = pLaunchKey;
}
void SequencerView::show()
{
	std::cout << "sequencer show" << std::endl;
	showPage(0);
}

bool SequencerView::receiveMidi(MidiMessage message)
{
return false;
}

