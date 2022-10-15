#include <VolcaBass.hpp>
#include <MenuState.hpp>
#include <Volcas.hpp>
#include <Sequencer.hpp>
#include <map>

void
VolcaBass::step(int pStep){
	//
	MidiMessage resetMessage = LaunchKey::DrumPadColor;
	resetMessage.data1    =  LaunchKey::DrumPads::DP10 + currentStep;
    resetMessage.data2    =  Volcas::BASS_MAIN;
    launchKey->SendMidiMessage(resetMessage);
	
	currentStep = pStep;
	MidiMessage colMessage = LaunchKey::DrumPadColorFlash;
	colMessage.data1    =    LaunchKey::DrumPads::DP10 + pStep;
    colMessage.data2    =  Volcas::BASS_ALT;
    launchKey->SendMidiMessage(colMessage);
    
    if(pStep == 0){
		colMessage = LaunchKey::DrumPadColor;
		int colors[4] = {Pots::OCT,Pots::VCO,Pots::VCO,Pots::VCO};
		for (int i = 0; i < 4; ++i)
		{
			colMessage.data1   =   LaunchKey::DrumPads::DP1 + i;
			colMessage.data2   = colors[i] ;
			launchKey->SendMidiMessage(colMessage);
		}
		colors[0] = Pots::LFO;
		colors[1] = Pots::LFO;
		colors[2] = 0;
		colors[3] = 0;
		for (int i = 0; i <	4; ++i)
		{
			colMessage.data1   = LaunchKey::DrumPads::DP5 + i;
			colMessage.data2   = colors[i] ;
			launchKey->SendMidiMessage(colMessage);
		}
	}else if(pStep == 1){
	
		colMessage = LaunchKey::DrumPadColor;
		int colors[4] = {Pots::EG,Pots::EG,Pots::EG,0};
		for (int i = 0; i < 4; ++i)
		{
			colMessage.data1   =   LaunchKey::DrumPads::DP1 + i;
			colMessage.data2   = colors[i] ;
			launchKey->SendMidiMessage(colMessage);
		}
		colors[0] = 0;
		colors[1] = Pots::SPECIAL;
		colors[2] = Pots::SPECIAL;
		colors[3] = Pots::SPECIAL;
		
		for (int i = 0; i <	4; ++i)
		{
			colMessage.data1   = LaunchKey::DrumPads::DP5 + i;
			colMessage.data2   = colors[i] ;
			launchKey->SendMidiMessage(colMessage);
		}
	}
    //
    
	
}


