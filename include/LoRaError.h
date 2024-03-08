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
    u_int64_t m_bitMaskValues;
    // Value m_lastValue;

public:
    LoRaError() = default;
    LoRaError(Value value) : m_bitMaskValues(value) /*, m_lastValue(value)*/ {}
    LoRaError(u_int64_t value) : m_bitMaskValues(value) /*, m_lastValue(value)*/ {}
    ~LoRaError() = default;

    // operator Value() const { return m_lastValue; }
    bool operator==(LoRaError other) const { return m_bitMaskValues == other.m_bitMaskValues; }
    bool operator!=(LoRaError other) const { return m_bitMaskValues != other.m_bitMaskValues; }
    // bool operator==(LoRaError::Value value) const { return m_lastValue == value; }
    // bool operator!=(LoRaError::Value value) const { return m_lastValue != value; }

    bool has(LoRaError other) const { return (m_bitMaskValues & other.m_bitMaskValues) == 1; }
    bool has(LoRaError::Value value) const { return (m_bitMaskValues & value) == 1; }
    bool hasNot(LoRaError other) const { return !this->has(other); }
    bool hasNot(LoRaError::Value value) const { return !this->has(value); }

    bool is(LoRaError other) const { return *this == other; }
    bool is(LoRaError::Value value) const { return *this == value; }
    bool isNot(LoRaError other) const { return !this->is(other); }
    bool isNot(LoRaError::Value value) const { return !this->is(value); }

    LoRaError operator|(const LoRaError &other) const { return LoRaError(m_bitMaskValues | other.m_bitMaskValues); };
    LoRaError &operator|=(const LoRaError &other) { m_bitMaskValues |= other.m_bitMaskValues; return *this; };

    // Implies that OK is "good"
    // explicit operator bool() const { return this->is(OK); };
    explicit operator bool() const = delete;

    bool operator==(LoRaError::Value value) const { return m_bitMaskValues == value; }
    bool operator!=(LoRaError::Value value) const { return m_bitMaskValues != value; }

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

#endif /* LORA_ERROR_H */