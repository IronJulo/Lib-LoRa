# This cmake file is used to generate the LoRaLibrary

add_library(LoRaLibrary STATIC LoRaDevice.cpp LoRaError.cpp)
target_include_directories(LoRaLibrary PUBLIC .)
target_include_directories(LoRaLibrary PUBLIC src)
target_include_directories(LoRaLibrary PUBLIC include)

target_link_libraries(LoRaLibrary PUBLIC EmbeddedCoreLibrary)