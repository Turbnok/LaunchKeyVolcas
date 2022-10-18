#include <ScreenState.hpp>
#include <midi.hpp>


// ScreenState::~ScreenState(){

// }
bool ScreenState::receiveMidi(MidiMessage message)
{
  // return 'z';
  std::cout << "coucouaa" << std::endl;
  if (message.channel)
  {
  }
  return false;
}
void ScreenState::init(MidiOut *pLaunchKey, MidiOut *pOut, MidiClock* pClock)
{
  out = pOut;
  midiClock = pClock;
  launchKey = pLaunchKey;
  const int* cols = getMenuColors();
  std::cout << cols[0] << std::endl;
  MidiMessage colMessage = LaunchKey::DrumPadColor;
  colMessage.data2 = 0;
  for (int i = 0; i < 4; ++i)
  {
    colMessage.data1 = LaunchKey::DrumPads::DP1 + i;
    launchKey->SendMidiMessage(colMessage);
  }
  for (int i = 0; i < 4; ++i)
  {
    colMessage.data1 = LaunchKey::DrumPads::DP5 + i;
    launchKey->SendMidiMessage(colMessage);
  }
  
  for (int i = 0; i < 4; ++i)
  {
  //  std::cout << cols[i] << std::endl;
    colMessage.data2 = cols[i];
    colMessage.data1 = LaunchKey::DrumPads::DP9 + i;
    launchKey->SendMidiMessage(colMessage);
  }
  colMessage.data2 = 0;
  for (int i = 0; i < 4; ++i)
  {
    colMessage.data2 = cols[i+4];
    colMessage.data1 = LaunchKey::DrumPads::DP13 + i;
    launchKey->SendMidiMessage(colMessage);
  }
  step(0);
}
void
ScreenState::step(int pStep){

}
void
ScreenState::gotoStep(int pStep){
  step(pStep);
}
ScreenState *
ScreenState::getState()
{
  return nextState;
}
