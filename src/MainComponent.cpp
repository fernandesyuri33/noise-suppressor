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

void MainComponent::prepareToPlay(int /*samplesPerBlockExpected*/, double /*sampleRate*/)
{
    // nothing to prepare for this simple pass-through example
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    // The buffer provided by AudioSourcePlayer already contains the microphone
    // input copied into the output channels. Leaving it untouched passes the
    // audio through without additional latency.
    juce::ignoreUnused(bufferToFill);
}

void MainComponent::releaseResources()
{
    // nothing to release
}

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void MainComponent::resized()
{
    deviceSelector.setBounds(getLocalBounds());
}
