#include <Sequencer.hpp>
#include <midi.hpp>
#include <vector>
#include <Config.hpp>

Sequencer::Sequencer()
{
	std::cout << "constructor" << std::endl;
}
Sequencer::~Sequencer()
{
	std::cout << "deconstructor" << std::endl;
}

void Sequencer::init(MidiOut *pLaunchKey, MidiOut *pOut, MidiClock *pClock)
{
	std::cout << "Sequecer Init" << std::endl;
	// ScreenState::init(pLaunchKey,pOut,pClock);
	out = pOut;
	midiClock = pClock;
	launchKey = pLaunchKey;
}
void Sequencer::play()
{
	playing = !playing;
	recording = records && playing;
}
void Sequencer::stop()
{
	playing = false;
	recording = false;
}
void Sequencer::record()
{
	records = !records;
	recording = records && playing;
}

void Sequencer::hide()
{
	std::cout << "hide sequencer" << std::endl;
	shown = false;
}
void Sequencer::show()
{
	std::cout << "sequencer show" << std::endl;
	shown = true;
	showPage(currentStep / 16);
}

void Sequencer::update()
{
	if (playing)
	{
		std::chrono::steady_clock::time_point elapsed = std::chrono::steady_clock::now();
		if ((std::chrono::duration_cast<std::chrono::milliseconds>(elapsed - last).count()) > interval)
		{
			if (shown)
			{
				MidiMessage colMessage = LaunchKey::DrumPadColor;
				colMessage.data1 = static_cast<LaunchKey::DrumPads>(LaunchKey::PADS[currentStep % 16]);
				colMessage.data2 = keysOn[currentStep] ? 29 : 0;
				launchKey->SendMidiMessage(colMessage);
			}
			currentDivision++;
			if (currentDivision == totalSteps * subdivisions)
			{
				currentDivision = 0;
			}
			currentStep = currentDivision/subdivisions;
			if (currentStep % 16 == 0 && shown)
			{
				// change page
				showPage(currentStep / 16);
			}

			last = elapsed;
			for (std::vector<MidiMessage>::iterator it = msg[currentDivision].begin(); it != msg[currentDivision].end(); ++it)
			{
				if (it->status != MidiStatus::UNDEF)
				{
					std::cout << "channel: " << it->channel
							  << " status: " << it->stat'us
							  << " data1: " << it->data1.value()
							  << " data2: " << it->data2.value() << std::endl;
					bool keypressed = false;
					for (long unsigned int i = 0; i < pressed.size(); i++)
					{
						if (pressed[i].data1.value() == it->data1.value())
						{
							keypressed = true;
							break;
						}
					}
					// std::cout << "keypresse: "<<keypressed  << std::endl;
					if (!keypressed)
					{
						it->channel = MidiChannel::CH1;
						out->SendMidiMessage(*it);
					}
				}
			}
			if (shown)
			{
				MidiMessage colMessage = LaunchKey::DrumPadColor;
				colMessage = LaunchKey::DrumPadColor;
				colMessage.data1 = static_cast<LaunchKey::DrumPads>(LaunchKey::PADS[currentStep % 16]);
				colMessage.data2 = 3;
				launchKey->SendMidiMessage(colMessage);
			}
		}
	}
}

void Sequencer::setRecord(bool pOnOff)
{
	records = pOnOff;
}
void Sequencer::showPage(int page)
{
	MidiMessage colMessage = LaunchKey::DrumPadColor;
	colMessage.data2 = 0;
	for (int i = 0; i < 16; i++)
	{
		LaunchKey::DrumPads pad = static_cast<LaunchKey::DrumPads>(LaunchKey::PADS[i]);
		colMessage.data1 = pad;
		colMessage.data2 = keysOn[i + (page * 16)] ? 29 : 0;
		launchKey->SendMidiMessage(colMessage);
	}
}

void Sequencer::receiveKeys(MidiMessage message)
{
	// ignore pitch or modulation
	if (message.status == MidiStatus::NON)
	{
		if (message.data2.value() == 0)
		{
			// note off
			int id = 1;
			for (long unsigned int i = 0; i < pressed.size(); i++)
			{
				if (pressed[i].data1.value() == message.data1.value())
				{
					id = i;
					break;
				}
			}
			pressed.erase(pressed.begin() + id);
			MidiMessage hello = MidiMessage(Config::keyChannel, message.status, message.data1.value(), message.data2.value());
			out->SendMidiMessage(hello);
		}
		else
		{
			// shut the privous note
			out->SendNoteOff(static_cast<MidiNote>(message.data1.value()), MidiChannel::CH1);
			MidiMessage hello = MidiMessage(Config::keyChannel, message.status, message.data1.value(), message.data2.value());
			out->SendMidiMessage(hello);
			pressed.push_back(message);
			if (recording)
			{
				keysOn[currentStep] = true;
			}
		}
	}
	if (recording)
	{
		if (message.status == MidiStatus::NOF)
		{
		}
		addMessage(message, currentDivision);
	}
}
void Sequencer::addMessage(MidiMessage pMessage, int pStep)
{
	
	msg[currentDivision].push_back(pMessage);
	MidiMessage msg = LaunchKey::DrumPadColor;
	msg.data1 = static_cast<LaunchKey::DrumPads>(LaunchKey::PADS[pStep/subdivisions]);
	msg.data2 = pMessage.data1.value();
	launchKey->SendMidiMessage(msg);
}
bool Sequencer::receiveMidi(MidiMessage message)
{
	std::cout << "Sequencer midi message : " << message.channel << std::endl;

	if (CompareMidiMessage(message, LaunchKey::Record))
	{
		record();
		MidiMessage recordMessage = LaunchKey::Record; // LaunchKey::DrumPadColor;
		if (!records)
		{
			recordMessage.data2 = 0;
		}
		launchKey->SendMidiMessage(recordMessage);
	}
	if (CompareMidiMessage(message, LaunchKey::Play))
	{
		play();
		MidiMessage playMessage = LaunchKey::Play;
		if (!playing)
		{
			playMessage.data2 = 0;
		}
		launchKey->SendMidiMessage(playMessage);
	}
	return false;
}
