#include "LoRaDevice.h"

LoRaDevice::LoRaDevice(ecl::Transport &transport,
                       ecl::AbstractGpio &reset,
                       ecl::AbstractGpio &dio0) : m_transport(transport),
                                                  m_reset(reset),
                                                  m_dio0(dio0),
                                                  m_state(LoRaState::WAITING){};

LoRaError LoRaDevice::init(long frequency)
{
    // m_chipSelect.setDirection(ecl::Gpio::Direction::OUTPUT);
    // m_chipSelect.setState(ecl::Gpio::State::HIGH);

    // if (m_reset){ // TODO boolify this
    if (true)
    {
        m_reset.setDirection(ecl::Gpio::Direction::OUTPUT);
        m_reset.setState(ecl::Gpio::State::LOW);
        // delay(10); // TODO mock time
        m_reset.setState(ecl::Gpio::State::HIGH);
        // delay(10); // TODO mock time
    }

    m_transport.begin();

    uint8_t version;
    readRegister(LoRaRegister::RegVersion, version);

    if (version != 0x12)
        return LoRaError::UNSUPPORTED_VERSION;

    sleep();
    setFrequency(frequency);

    return LoRaError::UNIMPLEMENTED;
}

LoRaError LoRaDevice::readRegister(uint8_t address, uint8_t &data)
{
    return transfer(address & 0x7f, data);
}

LoRaError LoRaDevice::writeRegister(uint8_t address, uint8_t value)
{
    return transfer(address | 0x80, value);
}

LoRaError LoRaDevice::transfer(uint8_t address, uint8_t &data)
{
    // m_chipSelect.setState(ecl::Gpio::State::LOW);
    if (ecl::Transaction transaction = m_transport.startTransaction())
    {
        transaction.transfer(address);
        uint8_t response = transaction.transfer(data);
        data = response;
    }
    else
    {
        return LoRaError::UNKNOWN; // TODO
    }
    // m_chipSelect.setState(ecl::Gpio::State::HIGH);

    return LoRaError::OK;
}

LoRaError LoRaDevice::sleep()
{
    return writeRegister(LoRaRegister::RegOpMode, LoRaMode::longRangeMode | LoRaMode::sleep);
}

LoRaError LoRaDevice::setFrequency(long frequency)
{
    m_frequency = frequency;

    /*
    from sx1276_77_78_79.pdf # 4.1.1 (p.37)

              
    Fstep = FXOSC / (2^19)
      ^       ^
      |       | 
      |       |
      |       Oscillator frequency
      Frequency step (smallest change in frequency that can be achieved)

    Ffr = Fstep * FRF(23, 0)
     ^      ^      ^
     |      |      |
     |      |      Frequency to insert into the registers
     |      Calculated before
     Frequency (function parameter)

    we can rewrite it as:

    FRF(23, 0) = (Ffr * (2^19)) / FXOSC
    
    int:
        From Sandeepmistry's Library
        
        uint64_t frf = ((uint64_t)frequency << 19) / FXOSC;
    */
   
    uint64_t frf = (double)frequency / ((double)FXOSC / (1 << 19));
    writeRegister(LoRaRegister::RegFrfMsb, (uint8_t)(((frf & 0b111111110000000000000000)) >> 16));
    writeRegister(LoRaRegister::RegFrfMid, (uint8_t)(((frf & 0b000000001111111100000000)) >> 8));
    writeRegister(LoRaRegister::RegFrfLsb, (uint8_t)(((frf & 0b000000000000000011111111)) >> 0));

    return LoRaError::OK; // TODO add a LoRaError res; res &= write...
}

LoRaError LoRaDevice::setSpreadingFactor(uint8_t spreadingFactor)
{
    return LoRaError::UNIMPLEMENTED;
}
 
LoRaError LoRaDevice::setCodingRate(uint8_t codingRade)
{
    return LoRaError::UNIMPLEMENTED;
}
 
LoRaError LoRaDevice::setBandwith(uint8_t bandwith)
{
    return LoRaError::UNIMPLEMENTED;
}
 
LoRaError LoRaDevice::setChannel(uint8_t channel)
{
    return LoRaError::UNIMPLEMENTED;
}
 