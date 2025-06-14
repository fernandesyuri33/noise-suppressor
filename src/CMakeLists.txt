set(SOURCE_FILES
    Main.cpp
    MainComponent.cpp
    NoiseCanceller.cpp
)

set(HEADER_FILES
    ${CMAKE_CURRENT_LIST_DIR}/../include/MainComponent.h
    ${CMAKE_CURRENT_LIST_DIR}/../include/NoiseCanceller.h
)

juce_add_gui_app(NoiseSuppressor
    PRODUCT_NAME "NoiseSuppressor")

target_sources(NoiseSuppressor PRIVATE ${SOURCE_FILES})

target_include_directories(NoiseSuppressor PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../include
)

target_link_libraries(NoiseSuppressor PRIVATE
    juce::juce_gui_extra
    juce::juce_audio_utils
)
