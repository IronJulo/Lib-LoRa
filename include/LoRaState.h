#ifndef LORA_STATE_H
#define LORA_STATE_H

enum class LoRaState {
    OK,
    WAITING,
    STANDBY,
    ERROR,

    UNKNOWN
};

#endif /* LORA_STATE_H */