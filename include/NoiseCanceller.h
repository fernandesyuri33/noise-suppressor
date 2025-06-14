#pragma once
#include <vector>
#include <juce_audio_basics/juce_audio_basics.h>

class NoiseCanceller
{
public:
    NoiseCanceller(size_t filterLength = 32, float stepSize = 0.001f);

    void prepare(double sampleRate, int maxBlockSize);
    void process(juce::AudioBuffer<float>& buffer, int startSample, int numSamples);

    void setEnabled(bool shouldBeEnabled);
    bool isEnabled() const noexcept;

private:
    size_t filterLength;
    float stepSize;
    bool enabled { true };

    std::vector<std::vector<float>> weights;
    std::vector<std::vector<float>> history;
};
