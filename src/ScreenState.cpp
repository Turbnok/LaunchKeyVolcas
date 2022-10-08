#include <ScreenState.hpp>
#include <midi.hpp>

	
bool
ScreenState::receiveMidi(MidiMessage message) 
{
  // return 'z';
  std::cout << "coucouaa" << std::endl;
  if(message.channel){
	  
  }
 return false;
}

void
ScreenState::init(MidiOut* pLaunchKey){
	launchKey = pLaunchKey;
}
ScreenState*
ScreenState::getState() 
{
  return nextState;
}
