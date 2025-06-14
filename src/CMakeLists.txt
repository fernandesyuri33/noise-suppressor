set(SOURCE_FILES
    Main.cpp
    MainComponent.cpp
    NoiseCanceller.cpp
    MacPermissions_mac.mm
)

set(HEADER_FILES
    ${CMAKE_CURRENT_LIST_DIR}/../include/MainComponent.h
    ${CMAKE_CURRENT_LIST_DIR}/../include/NoiseCanceller.h
    ${CMAKE_CURRENT_LIST_DIR}/../include/mac/MacPermissions.h
)

juce_add_gui_app(NoiseSuppressor
    PRODUCT_NAME "NoiseSuppressor"
    MICROPHONE_PERMISSION_ENABLED TRUE
    MICROPHONE_PERMISSION_TEXT "NoiseSuppressor requires microphone access to process audio")

target_sources(NoiseSuppressor PRIVATE ${SOURCE_FILES})

target_include_directories(NoiseSuppressor PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../include
    ${CMAKE_CURRENT_LIST_DIR}/../include/mac
)

target_link_libraries(NoiseSuppressor PRIVATE
    juce::juce_gui_extra
    juce::juce_audio_utils
)
