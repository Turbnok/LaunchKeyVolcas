#include <Sequencer.hpp>
#include <midi.hpp>

Sequencer::Sequencer(){
	std::cout << "constructor" << std::endl;
}
Sequencer::~Sequencer(){
	std::cout << "deconstructor" << std::endl;
}

void 
Sequencer::init(MidiOut* pLaunchKey,MidiOut* pOut){
    std::cout << "Sequecer Init" << std::endl;    
	ScreenState::init(pLaunchKey,pOut);		
	MidiMessage colMessage = LaunchKey::DrumPadColor;
    colMessage.data2   =   0;
	for (int i = 0; i < 4; ++i)
	{
		pads[i] = LaunchKey::DrumPads::DP1 + i;
		colMessage.data1 = LaunchKey::DrumPads::DP1 + i;
		launchKey->SendMidiMessage(colMessage);
	}
	for (int i = 0; i < 4; ++i)
	{
		pads[i+4] = LaunchKey::DrumPads::DP5 + i;
		colMessage.data1 = LaunchKey::DrumPads::DP5 + i;
		launchKey->SendMidiMessage(colMessage);
	}
    for (int i = 0; i < 4; ++i)
    {
		pads[i+8] =  LaunchKey::DrumPads::DP9 + i;
        colMessage.data1 = LaunchKey::DrumPads::DP9 + i;
        launchKey->SendMidiMessage(colMessage);
    }
	for (int i = 0; i < 4; ++i)
	{
		pads[i+12] =  LaunchKey::DrumPads::DP13 + i;
		colMessage.data1 = LaunchKey::DrumPads::DP13 + i;
		launchKey->SendMidiMessage(colMessage);
	}	
}

void 
Sequencer::update(){
    std::chrono::steady_clock::time_point elapsed = std::chrono::steady_clock::now();  
    if ((std::chrono::duration_cast<std::chrono::milliseconds> (elapsed - last).count()) > interval)
    {
        MidiMessage colMessage = LaunchKey::DrumPadColor;
		colMessage.data1   =   pads[currentStep];
		colMessage.data2   =   0;
		launchKey->SendMidiMessage(colMessage);

		currentStep++;
        if (currentStep == totalSteps)
        {
            currentStep = 0;
        }
        last = elapsed;		

		colMessage = LaunchKey::DrumPadColor;
		colMessage.data1   =   pads[currentStep];
		colMessage.data2   =   32;
		launchKey->SendMidiMessage(colMessage);
    }
}

bool
Sequencer::receiveMidi(MidiMessage message){
	std::cout << "menu state midi message : " << message.channel << std::endl;
	std::cout << " : " << message.data1.value() << std::endl;
	if(message.data2.value() ==0) return false;
	if(message.data1.value() == LaunchKey::DrumPads::DP9){

		return true;
	}
	if(message.data1.value() == LaunchKey::DrumPads::DP10){

		return true;
	}
	if(message.channel == 15){
		// pots
		
		tempo =  message.data2.value();
		interval = 60000 / tempo / 4;
	}
	return false;
}



