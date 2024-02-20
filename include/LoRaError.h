#ifndef LORA_ERROR_H
#define LORA_ERROR_H

enum class LoRaError {
    OK = 1,
    UNIMPLEMENTED = 2,
    UNSUPPORTED_VERSION = 4,
    UNKNOWN,
};

#endif /* LORA_ERROR_H */