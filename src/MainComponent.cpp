#include "MainComponent.h"

MainComponent::MainComponent()
    : deviceSelector(deviceManager, 1, 2, 1, 2, false, false, true, false)
{
    juce::PropertiesFile::Options opts;
    opts.applicationName     = "NoiseSuppressor";
    opts.filenameSuffix      = "settings";
    opts.osxLibrarySubFolder = "Application Support";
    properties.reset(new juce::PropertiesFile(opts));

    addAndMakeVisible(deviceSelector);
    addAndMakeVisible(startButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(enableToggle);
    addAndMakeVisible(cpuLabel);

    startButton.onClick = [this] { startAudio(); };
    stopButton.onClick  = [this] { stopAudio(); };
    enableToggle.onClick = [this] { setNoiseCancellationEnabled(enableToggle.getToggleState()); };

    cpuLabel.setJustificationType(juce::Justification::centredLeft);

    loadSettings();
    startTimerHz(2);
    setSize(600, 400);
}

MainComponent::~MainComponent()
{
    saveSettings();
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
    auto area = getLocalBounds();
    auto top = area.removeFromTop(30);
    startButton.setBounds(top.removeFromLeft(80).reduced(2));
    stopButton.setBounds(top.removeFromLeft(80).reduced(2));
    enableToggle.setBounds(top.removeFromLeft(200).reduced(2));
    cpuLabel.setBounds(top.removeFromLeft(100).reduced(2));
    deviceSelector.setBounds(area);
}

void MainComponent::startAudio()
{
    if (audioRunning)
        return;

    std::unique_ptr<juce::XmlElement> xml;
    if (properties != nullptr)
    {
        auto xmlStr = properties->getValue("deviceState");
        if (xmlStr.isNotEmpty())
            xml = juce::XmlDocument::parse(xmlStr);
    }

    setAudioChannels(2, 2, xml.get());
    audioRunning = true;
    startButton.setEnabled(false);
    stopButton.setEnabled(true);
}

void MainComponent::stopAudio()
{
    if (! audioRunning)
        return;

    shutdownAudio();
    audioRunning = false;
    startButton.setEnabled(true);
    stopButton.setEnabled(false);
}

void MainComponent::loadSettings()
{
    std::unique_ptr<juce::XmlElement> xml;
    bool enabled = true;

    if (properties != nullptr)
    {
        auto xmlStr = properties->getValue("deviceState");
        if (xmlStr.isNotEmpty())
            xml = juce::XmlDocument::parse(xmlStr);

        enabled = properties->getBoolValue("noiseEnabled", true);
    }

    setAudioChannels(2, 2, xml.get());
    audioRunning = true;

    startButton.setEnabled(false);
    stopButton.setEnabled(true);
    enableToggle.setToggleState(enabled, juce::dontSendNotification);
    setNoiseCancellationEnabled(enabled);
}

void MainComponent::saveSettings()
{
    if (properties != nullptr)
    {
        if (auto xml = deviceManager.createStateXml())
            properties->setValue("deviceState", xml->toString());

        properties->setValue("noiseEnabled", enableToggle.getToggleState());
        properties->saveIfNeeded();
    }
}

void MainComponent::timerCallback()
{
    const auto cpu = deviceManager.getCpuUsage() * 100.0;
    cpuLabel.setText(juce::String(cpu, 2) + "% CPU", juce::dontSendNotification);
}
