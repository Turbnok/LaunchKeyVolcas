#include <midi.hpp>

bool CompareMidiMessage(MidiMessage messageA, MidiMessage messageB)
{
    return messageA.channel == messageB.channel &&
           messageA.status == messageB.status &&
           messageA.data1.value() == messageB.data1.value() &&
           messageA.data2.value() == messageB.data2.value();
}

MidiIn::MidiIn()
{
    midiIn = std::make_unique<RtMidiIn>();
}

std::vector<std::string> &
MidiIn::GetPorts(void)
{
    ports.clear();
    std::uint8_t numPorts = midiIn->getPortCount();
    for (std::uint8_t i = 0; i < numPorts; ++i)
        ports.push_back(midiIn->getPortName(i));
    return ports;
}

bool MidiIn::IsPortOpen(void)
{
    return midiIn->isPortOpen();
}
void MidiIn::clockCallBack( double deltatime, std::vector< unsigned char > *message, void *user )
{
  unsigned int *clock_count = reinterpret_cast<unsigned int*>(user);
  // Ignore longer messages
  if (message->size() != 1)
    return;

  unsigned int msg = message->at(0);
  if (msg == 0xFA)
    std::cout << "START received" << std::endl;
  if (msg == 0xFB)
    std::cout << "CONTINUE received" << std::endl;
  if (msg == 0xFC)
    std::cout << "STOP received" << std::endl;
  if (msg == 0xF8) {
    if (++*clock_count == 24) {
      double bpm = 60.0 / 24.0 / deltatime;
      std::cout << "One beat, estimated BPM = " << bpm <<std::endl;
      *clock_count = 0;
    }
  }
  else
    *clock_count = 0;
}
void MidiIn::OpenPort(std::uint8_t numPort,std::string name)
{
    //midiIn->setCallback( &clockCallBack, &clock_count );
    unsigned int numPorts = midiIn->getPortCount();
    if (numPort < numPorts)
        midiIn->openPort(numPort,name+ " Input");
    else
        midiIn->openPort(0,name  + " Input");
    midiIn->setClientName(name);
    midiIn->ignoreTypes(false, false, false);

}

void MidiIn::ClosePort(void)
{
    midiIn->closePort();
}

void MidiIn::clock(void)
{
    if (!midiIn->isPortOpen())
        return; // std::nullopt;
        
    midiIn->getMessage(&message);
    
    if (message.size() == 0)
    {
        return;
    }
    if (message.at(0) == MidiStatus::CLK)
    {
        
        if (++clock_count == 24)
        {
            double bpm = 60.0 / 24.0 / 16;
            std::cout << "One beat, estimated BPM = " << bpm << std::endl;
            clock_count = 0;
        }
    } // skip clock sync
}

std::optional<MidiMessage>
MidiIn::GetMidiMessage(void)
{
    if (!midiIn->isPortOpen())
        return std::nullopt;

    midiIn->getMessage(&message);
    if (message.size() == 0)
        return std::nullopt;

    MidiMessage midiMessage;
    if (message.at(0) < 0xF0)
    {
        midiMessage.status = MidiStatus(message.at(0) & 0xF0);
        midiMessage.channel = MidiChannel(message.at(0) & 0x0F);
        if (message.size() > 1)
            midiMessage.data1 = std::make_optional(message.at(1));
        if (message.size() > 2)
            midiMessage.data2 = std::make_optional(message.at(2));

        if (midiMessage.status == MidiStatus::CC)
        {
            CC.at(midiMessage.channel).at(*midiMessage.data1) = *midiMessage.data2;
        }
    }
    else
    {
        if (message.at(0) == MidiStatus::CLK)
        {
            return std::nullopt;
            //std::cout << "click" << std::endl;
            // if (++clock_count == 24) {
            //     double bpm = 60.0 / 24.0 / deltatime;
            //     std::cout << "One beat, estimated BPM = " << bpm <<std::endl;
            //     *clock_count = 0;
            // }
        } // skip clock sync
    }
    return std::make_optional(midiMessage);
}

double
MidiIn::GetCCValue(std::uint8_t numCh, std::uint8_t numCtrl)
{
    std::uint8_t val = CC.at(numCh).at(numCtrl);
    return val / 127.0;
}

MidiOut::MidiOut()
{
    midiOut = std::make_unique<RtMidiOut>();
}

std::vector<std::string> &
MidiOut::GetPorts(void)
{
    ports.clear();
    std::uint8_t numPorts = midiOut->getPortCount();
    for (std::uint8_t i = 0; i < numPorts; ++i)
        ports.push_back(midiOut->getPortName(i));
    return ports;
}

void MidiOut::OpenPort(std::uint8_t numPort,std::string name)
{
    midiOut->setClientName(name);
    unsigned int numPorts = midiOut->getPortCount();
    if (numPort < numPorts)
        midiOut->openPort(numPort, name + " Output");
    else
        midiOut->openPort(0, name  + " Output");
    
}

void MidiOut::ClosePort(void)
{
    midiOut->closePort();
}

bool MidiOut::IsPortOpen(void)
{
    return midiOut->isPortOpen();
}

void MidiOut::SendMidiMessage(MidiMessage midiMessage)
{
    if (!midiOut->isPortOpen())
        return;
    message.clear();
    message.push_back(midiMessage.status + midiMessage.channel);
    if (midiMessage.data1)
        message.push_back(*midiMessage.data1);
    if (midiMessage.data2)
        message.push_back(*midiMessage.data2);

    if (midiOut)
        midiOut->sendMessage(&message);
}


MidiClock::MidiClock()
{
    midiIn = std::make_unique<RtMidiIn>();
}

std::vector<std::string> &
MidiClock::GetPorts(void)
{
    ports.clear();
    std::uint8_t numPorts = midiIn->getPortCount();
    for (std::uint8_t i = 0; i < numPorts; ++i)
        ports.push_back(midiIn->getPortName(i));
    return ports;
}

bool MidiClock::IsPortOpen(void)
{
    return midiIn->isPortOpen();
}
void MidiClock::clockCallBack( double deltatime, std::vector< unsigned char > *message, void *user )
{
  unsigned int *clock_count = reinterpret_cast<unsigned int*>(user);
  // Ignore longer messages
  if (message->size() != 1)
    return;

  unsigned int msg = message->at(0);
  if (msg == 0xFA)
    std::cout << "START received" << std::endl;
  if (msg == 0xFB)
    std::cout << "CONTINUE received" << std::endl;
  if (msg == 0xFC)
    std::cout << "STOP received" << std::endl;
  if (msg == 0xF8) {
    if (++*clock_count == 24) {
    
      double bpm = 60.0 / 24.0 / deltatime;
      std::cout << "One beat, estimated BPM = " << bpm << " : " << deltatime <<std::endl;
      *clock_count = 0;
    }
  }
  else
    *clock_count = 0;
}
void MidiClock::OpenPort(std::uint8_t numPort,std::string name)
{
    midiIn->setCallback( &clockCallBack, &clock_count );
    unsigned int numPorts = midiIn->getPortCount();
    if (numPort < numPorts)
        midiIn->openPort(numPort,name+ " Input");
    else
        midiIn->openPort(0,name  + " Input");
    midiIn->setClientName(name);
    midiIn->ignoreTypes(true, false, true);

}

void MidiClock::ClosePort(void)
{
    midiIn->closePort();
}

void MidiClock::clock(void)
{
    if (!midiIn->isPortOpen())
        return; // std::nullopt;
        
    midiIn->getMessage(&message);
    
    if (message.size() == 0)
    {
        return;
    }
    if (message.at(0) == MidiStatus::CLK)
    {
        
        if (++clock_count == 24)
        {
            double bpm = 60.0 / 24.0 / 16;
            std::cout << "One beat, estimated BPM = " << bpm << std::endl;
            clock_count = 0;
        }
    } // skip clock sync
}

std::optional<MidiMessage>
MidiClock::GetMidiMessage(void)
{
    if (!midiIn->isPortOpen())
        return std::nullopt;

    midiIn->getMessage(&message);
    if (message.size() == 0)
        return std::nullopt;

    MidiMessage midiMessage;
    if (message.at(0) < 0xF0)
    {
        midiMessage.status = MidiStatus(message.at(0) & 0xF0);
        midiMessage.channel = MidiChannel(message.at(0) & 0x0F);
        if (message.size() > 1)
            midiMessage.data1 = std::make_optional(message.at(1));
        if (message.size() > 2)
            midiMessage.data2 = std::make_optional(message.at(2));

        if (midiMessage.status == MidiStatus::CC)
        {
            CC.at(midiMessage.channel).at(*midiMessage.data1) = *midiMessage.data2;
        }
    }
    else
    {
        if (message.at(0) == MidiStatus::CLK)
        {
            return std::nullopt;
            //std::cout << "click" << std::endl;
            // if (++clock_count == 24) {
            //     double bpm = 60.0 / 24.0 / deltatime;
            //     std::cout << "One beat, estimated BPM = " << bpm <<std::endl;
            //     *clock_count = 0;
            // }
        } // skip clock sync
    }
    return std::make_optional(midiMessage);
}

double
MidiClock::GetCCValue(std::uint8_t numCh, std::uint8_t numCtrl)
{
    std::uint8_t val = CC.at(numCh).at(numCtrl);
    return val / 127.0;
}