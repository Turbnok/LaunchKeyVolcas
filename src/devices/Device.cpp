#include <Device.hpp>
#include <MenuState.hpp>
#include <Volcas.hpp>
#include <map>

void Device::step(int pStep)
{
	std::cout << "couc";
}

bool Device::receiveMidi(MidiMessage message)
{
	std::cout << "Device midi message" << message.channel << std::endl;
	if (message.data2.value() == 0)
		return false;
	// back
	if (message.data1 == LaunchKey::DrumPads::DP9)
	{
		nextState = new MenuState;
		return true;
	}

	/*
	 if(CompareMidiMessage(message,LaunchKey::ArrUp)){
		 nextState = new Sequencer;
		 return true;
	 }
	 */

	if (message.channel == 15)
	{
		// pots
		MidiMessage sendMessage = LaunchKey::DrumPadColor;
		sendMessage.channel = getChannel();
		sendMessage.status = MidiStatus::CC;
		sendMessage.data2 = message.data2.value();
		std::cout << getCurrentStep() << std::endl;
		if (getCurrentStep() == 0)
		{
			if (mapStep0.count(message.data1.value()) > 0)
			{
				sendMessage.data1 = getMap().at(message.data1.value());
				out->SendMidiMessage(sendMessage);
			}
		}
		else if (getCurrentStep() == 1)
		{
			if (mapStep1.count(message.data1.value()) > 0)
			{
				sendMessage.data1 = getMap().at(message.data1.value());
				out->SendMidiMessage(sendMessage);
			}
		}
	}

	if (message.data1.value() == LaunchKey::DrumPads::DP10)
	{
		step(0);
	}
	if (message.data1.value() == LaunchKey::DrumPads::DP11)
	{
		step(1);
	}
	// if(message.data1.value() == LaunchKey::DrumPads::DP11){
	// 	std::cout << "P111" << message.channel << std::endl;
	// 	MidiMessage playMessage = LaunchKey::DrumPadColor;
	// 	playMessage.channel = MidiChannel::CH1;
	// 	playMessage.status = MidiStatus::START;
	// 	playMessage.data2    = 0;
	// 	playMessage.data1    = 0x1;
	// 	out->SendMidiMessage(playMessage);
	// 	return false;
	// }
	return false;
}

void Device::gotoStep(int pStep)
{
	step(pStep);
}
ScreenState *
Device::getState()
{
	return nextState;
}
