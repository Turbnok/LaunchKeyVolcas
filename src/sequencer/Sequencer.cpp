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
	mode = Modes::HIDDEN;
}
void Sequencer::show()
{
	std::cout << "sequencer show" << std::endl;
	mode = Modes::SEQUENCER;
	showPage(currentStep / 16);
}
void Sequencer::showMenu()
{


}
void Sequencer::hideMenu()
{

}
void Sequencer::update()
{
	if (playing)
	{

		std::chrono::steady_clock::time_point elapsed = std::chrono::steady_clock::now();
		if ((std::chrono::duration_cast<std::chrono::milliseconds>(elapsed - last).count()) > interval)
		{
			if (mode == Modes::SEQUENCER)
			{
				MidiMessage colMessage = LaunchKey::DrumPadColor;
				colMessage.data1 = static_cast<LaunchKey::DrumPads>(LaunchKey::PADS[currentStep % 16]);
				colMessage.data2 = track.sequence->keysOn[currentStep] ? 29 : 0;
				launchKey->SendMidiMessage(colMessage);
			}
			currentDivision++;
			if (currentDivision == totalSteps * subdivisions)
			{
				currentDivision = 0;
			}
			currentStep = currentDivision/subdivisions;
			if (currentStep % 16 == 0 && (mode == Modes::SEQUENCER))
			{
				// change page
				showPage(currentStep / 16);
			}

			last = elapsed;
			
			for (std::vector<MidiMessage>::iterator it = track.sequence->msg[currentDivision].begin(); it !=track.sequence->msg[currentDivision].end(); ++it)
			{
				 if (it->status != MidiStatus::UNDEF)
				 {
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
						it->channel = Config::keyChannel;
						out->SendMidiMessage(*it);
					}
				}
			}
			if (mode == Modes::SEQUENCER)
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


	for (int i = 0; i < 16; i++)
	{
		LaunchKey::DrumPads pad = static_cast<LaunchKey::DrumPads>(LaunchKey::PADS[i]);
		colMessage.data1 = pad;
		colMessage.data2 = track.sequence->keysOn[i + (page * 16)] ? 29 : 0;
		launchKey->SendMidiMessage(colMessage);
	}
}

void Sequencer::receiveKeys(MidiMessage message)
{
	// ignore pitch or modulation
	if (message.status == MidiStatus::NOF)
	{
		
	}	
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
			out->SendNoteOff(static_cast<MidiNote>(message.data1.value()), Config::keyChannel);
			MidiMessage hello = MidiMessage(Config::keyChannel, message.status, message.data1.value(), 127);
			std::cout << "channel " << Config::keyChannel << std::endl;
			out->SendMidiMessage(hello);
			pressed.push_back(message);
			if (recording)
			{
				track.sequence->keysOn[currentStep] = true;
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
	track.sequence->addMessage(pMessage, pStep);
	MidiMessage msg = LaunchKey::DrumPadColor;
	msg.data1 = static_cast<LaunchKey::DrumPads>(LaunchKey::PADS[pStep/subdivisions]);
	msg.data2 = pMessage.data1.value();
	launchKey->SendMidiMessage(msg);
}
bool Sequencer::receiveMidi(MidiMessage message)
{
	std::cout << "Sequencer receive midi : " << message.data1.value() <<":"<< message.data2.value() << std::endl;
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
	if (message.data1.value() == LaunchKey::DP16 && shift){
		
		track.sequence->clear();
		pressed.clear();
		showPage(0);
	}
	if (message.data1.value() == LaunchKey::ArrDown.data1.value())
	{
		shift = message.data2.value() != 0;
		std::cout << "Sequencer down : " << shift << std::endl;

	}
	return false;
}

