# This cmake file is used to generate the LoRaLibrary

add_library(LoRaLibrary INTERFACE)
target_include_directories(LoRaLibrary INTERFACE .)
target_include_directories(LoRaLibrary INTERFACE src)
target_include_directories(LoRaLibrary INTERFACE include)

target_link_libraries(LoRaLibrary INTERFACE EmbeddedCoreLibrary)