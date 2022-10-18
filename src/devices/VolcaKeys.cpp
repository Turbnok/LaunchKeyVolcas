#include <VolcaKeys.hpp>
#include <MenuState.hpp>
#include <Volcas.hpp>
#include <map>


void
VolcaKeys::step(int pStep){
	//
	MidiMessage resetMessage = LaunchKey::DrumPadColor;
	resetMessage.data1    =  LaunchKey::DrumPads::DP10 + currentStep;
    resetMessage.data2    =  Volcas::KEYS_MAIN;
    launchKey->SendMidiMessage(resetMessage);
	
	currentStep = pStep;
	MidiMessage colMessage = LaunchKey::DrumPadColorFlash;
	colMessage.data1    =    LaunchKey::DrumPads::DP10 + pStep;
    colMessage.data2    =  Volcas::KEYS_ALT;
    launchKey->SendMidiMessage(colMessage);
    
    if(pStep == 0){
		colMessage = LaunchKey::DrumPadColor;
		int colors[4] = {Pots::OCT,Pots::OCT,Pots::VCO,Pots::VCO};
		for (int i = 0; i < 4; ++i)
		{
			colMessage.data1   =   LaunchKey::DrumPads::DP1 + i;
			colMessage.data2   = colors[i] ;
			launchKey->SendMidiMessage(colMessage);
		}
		colors[0] = Pots::VCO;
		colors[1] = Pots::VCF;
		colors[2] = 0;
		colors[3] = Pots::VCF;
		for (int i = 0; i <	4; ++i)
		{
			colMessage.data1   = LaunchKey::DrumPads::DP5 + i;
			colMessage.data2   = colors[i] ;
			launchKey->SendMidiMessage(colMessage);
		}
	}else if(pStep == 1){
	
		colMessage = LaunchKey::DrumPadColor;
		int colors[4] = { Pots::LFO,Pots::LFO,Pots::LFO,Pots::EG};
		for (int i = 0; i < 4; ++i)
		{
			colMessage.data1   =   LaunchKey::DrumPads::DP1 + i;
			colMessage.data2   = colors[i] ;
			launchKey->SendMidiMessage(colMessage);
		}
		colors[0] = Pots::EG;
		colors[1] = Pots::EG;
		colors[2] = Pots::DELAY;
		colors[3] = Pots::DELAY;
		
		for (int i = 0; i <	4; ++i)
		{
			colMessage.data1   = LaunchKey::DrumPads::DP5 + i;
			colMessage.data2   = colors[i] ;
			launchKey->SendMidiMessage(colMessage);
		}
	}
    //
}
