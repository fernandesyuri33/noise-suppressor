#include "MainComponent.h"

MainComponent::MainComponent()
    : deviceSelector(deviceManager, 1, 2, 1, 2, false, false, true, false)
{
    addAndMakeVisible(deviceSelector);

    // request one input and two output channels by default
    setAudioChannels(2, 2);

    setSize(600, 400);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    noiseCanceller.prepare(sampleRate, samplesPerBlockExpected);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    // The buffer already contains the microphone input copied to the output
    // channels. Process the buffer to produce an inverse waveform.
    noiseCanceller.process(*bufferToFill.buffer, bufferToFill.startSample, bufferToFill.numSamples);
}

void MainComponent::releaseResources()
{
    // nothing to release
}

void MainComponent::setNoiseCancellationEnabled(bool enabled)
{
    noiseCanceller.setEnabled(enabled);
}

bool MainComponent::isNoiseCancellationEnabled() const noexcept
{
    return noiseCanceller.isEnabled();
}

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void MainComponent::resized()
{
    deviceSelector.setBounds(getLocalBounds());
}
