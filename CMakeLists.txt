cmake_minimum_required(VERSION 3.15)
project(NoiseSuppressor VERSION 0.1.0)

add_subdirectory(JUCE)
add_subdirectory(src)

target_link_libraries(NoiseSuppressor
    PRIVATE
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_processors
)
