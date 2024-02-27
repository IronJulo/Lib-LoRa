#ifndef LORA_ERROR_H
#define LORA_ERROR_H

class LoRaError
{
public:
    enum Value
    {
        OK,
        UNIMPLEMENTED,
        UNSUPPORTED_VERSION,

        UNKNOWN,
    };

private:
    Value m_value;

public:
    LoRaError() = default;
    LoRaError(Value value) : m_value(value) {}
    ~LoRaError() = default;
    operator Value() const { return m_value; }

    explicit operator bool() const = delete;
    bool operator==(LoRaError other) const { return m_value == other.m_value; }
    bool operator!=(LoRaError other) const { return m_value != other.m_value; }

    const char *toString() const
    {
        switch (m_value)
        {
        case Value::OK:
            return "OK";
            break;
        case Value::UNIMPLEMENTED:
            return "UNIMPLEMENTED";
            break;
        case Value::UNSUPPORTED_VERSION:
            return "UNSUPPORTED_VERSION";
            break;
        default:
            return "UNKNOWN";
            break;
        }
    }
};

#endif /* LORA_ERROR_H */