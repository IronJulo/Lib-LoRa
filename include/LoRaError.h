#ifndef LORA_ERROR_H
#define LORA_ERROR_H

#include <string>
#include <stdint.h>

class LoRaError
{
public:
    enum Value
    {
        OK = 0b1,
        UNIMPLEMENTED = 0b10,
        READ_ERROR = 0b100,
        WRITE_ERROR = 0b1000,
        UNSUPPORTED_VERSION = 0b10000,
        TRANSACTION_ERROR = 0b100000,

        UNKNOWN //= 0b1000000000000000000000000000000000000000000000000000000000000000,
    };

private:
    uint64_t m_bitMaskValues;
    // Value m_lastValue;

public:
    LoRaError() = default;
    LoRaError(Value value) : m_bitMaskValues(value) /*, m_lastValue(value)*/ {}
    LoRaError(uint64_t value) : m_bitMaskValues(value) /*, m_lastValue(value)*/ {}
    ~LoRaError() = default;

    uint64_t getBitMaskValue() const { return m_bitMaskValues; }

    // operator Value() const { return m_lastValue; }
    bool operator==(const LoRaError &other) const { return m_bitMaskValues == other.m_bitMaskValues; }
    bool operator!=(const LoRaError &other) const { return m_bitMaskValues != other.m_bitMaskValues; }

    bool operator==(const LoRaError::Value &value) const { return m_bitMaskValues == value; }
    bool operator!=(const LoRaError::Value &value) const { return m_bitMaskValues != value; }

    bool has(const LoRaError &other) const { return (m_bitMaskValues & other.m_bitMaskValues) == 1; }
    bool has(const LoRaError::Value &value) const { return (m_bitMaskValues & value) == 1; }
    bool hasNot(const LoRaError &other) const { return !this->has(other); }
    bool hasNot(const LoRaError::Value &value) const { return !this->has(value); }

    bool is(const LoRaError &other) const { return *this == other; }
    bool is(const LoRaError::Value &value) const { return *this == value; }
    bool isNot(const LoRaError &other) const { return !this->is(other); }
    bool isNot(const LoRaError::Value &value) const { return !this->is(value); }

    LoRaError operator|(const LoRaError &other) const { return LoRaError(m_bitMaskValues | other.m_bitMaskValues); };
    LoRaError &operator|=(const LoRaError &other)
    {
        m_bitMaskValues |= other.m_bitMaskValues;
        return *this;
    };

    // Implies that OK is "good"
    // explicit operator bool() const { return this->is(OK); };
    explicit operator bool() const = delete;

    // TODO activate only on debug (dynamic memory allocated here)
    const std::string toString() const
    {
        std::string result;
        int mask = 1;
        uint64_t bitMaskCopy = m_bitMaskValues;
        while (bitMaskCopy)
        {
            switch (bitMaskCopy & mask)
            {
            case Value::OK:
                result += "OK";
                break;
            case Value::UNIMPLEMENTED:
                result += "UNIMPLEMENTED";
                break;
            case Value::READ_ERROR:
                result += "READ_ERROR";
                break;
            case Value::WRITE_ERROR:
                result += "WRITE_ERROR";
                break;
            case Value::UNSUPPORTED_VERSION:
                result += "UNSUPPORTED_VERSION";
                break;
            }
            result += ", ";
            bitMaskCopy &= ~mask;
            mask <<= 1;
        }
        return result;
    }
};

bool operator==(const LoRaError::Value &value, const LoRaError &error);
bool operator!=(const LoRaError::Value &value, const LoRaError &error);

// bool operator==(LoRaError const &error, LoRaError::Value const &value);
// bool operator!=(LoRaError const &error, LoRaError::Value const &value);

#endif /* LORA_ERROR_H */