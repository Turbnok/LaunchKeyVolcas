
#include <ScreenState.hpp>
#include <midi.hpp>

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
  show();
  step(0);
}
void
ScreenState::show(){
  shown = true;
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
  gotoStep(currentStep);
}

void
ScreenState::hide(){
  shown = false;
}
void
ScreenState::step(int pStep){

}
void
ScreenState::gotoStep(int pStep){
  currentStep = pStep;
  step(pStep);
}
ScreenState *
ScreenState::getState()
{
  return nextState;
}
Screens::Name
ScreenState::getName()
{
  return Screens::Menu;
}

