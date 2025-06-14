#pragma once
#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_data_structures/juce_data_structures.h>
#include "NoiseCanceller.h"

class MainComponent : public juce::AudioAppComponent,
                      private juce::Timer
{
public:
    MainComponent();
    ~MainComponent() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    void paint(juce::Graphics& g) override;
    void resized() override;

    void setNoiseCancellationEnabled(bool enabled);
    bool isNoiseCancellationEnabled() const noexcept;

private:
    void timerCallback() override;
    void startAudio();
    void stopAudio();
    void loadSettings();
    void saveSettings();
    void openAudioWithXml(const juce::String& xmlState);
    juce::AudioDeviceSelectorComponent deviceSelector;
    NoiseCanceller noiseCanceller;
    juce::TextButton startButton { "Start" };
    juce::TextButton stopButton  { "Stop" };
    juce::ToggleButton enableToggle { "Enable Noise Cancellation" };
    juce::Label cpuLabel;

    bool audioRunning { false };
    std::unique_ptr<juce::PropertiesFile> properties;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
