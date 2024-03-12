#include "LoRaError.h"

bool operator==(const LoRaError::Value &value, const LoRaError &error) { return error.is(value); }
bool operator!=(const LoRaError::Value &value, const LoRaError &error) { return error.isNot(value); }

// bool operator==(LoRaError const &error, LoRaError::Value const &value) { return error.is(value); }
// bool operator!=(LoRaError const &error, LoRaError::Value const &value) { return error.isNot(value); }