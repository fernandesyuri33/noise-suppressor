#include "NoiseCanceller.h"

NoiseCanceller::NoiseCanceller(size_t len, float step)
    : filterLength(len), stepSize(step)
{
}

void NoiseCanceller::prepare(double /*sampleRate*/, int /*maxBlockSize*/)
{
    weights.clear();
    history.clear();
}

void NoiseCanceller::setEnabled(bool shouldBeEnabled)
{
    enabled = shouldBeEnabled;
}

bool NoiseCanceller::isEnabled() const noexcept
{
    return enabled;
}

void NoiseCanceller::process(juce::AudioBuffer<float>& buffer, int startSample, int numSamples)
{
    if (! enabled)
        return;

    const int numChannels = buffer.getNumChannels();
    if ((int) weights.size() != numChannels)
    {
        weights.assign(numChannels, std::vector<float>(filterLength, 0.0f));
        history.assign(numChannels, std::vector<float>(filterLength, 0.0f));
    }

    for (int ch = 0; ch < numChannels; ++ch)
    {
        auto* data = buffer.getWritePointer(ch, startSample);
        auto& w = weights[ch];
        auto& h = history[ch];

        for (int n = 0; n < numSamples; ++n)
        {
            float x = data[n];

            // shift history
            for (size_t k = filterLength - 1; k > 0; --k)
                h[k] = h[k - 1];
            h[0] = x;

            float y = 0.0f;
            for (size_t k = 0; k < filterLength; ++k)
                y += w[k] * h[k];

            float error = x - y; // residual signal after cancelling prediction
            for (size_t k = 0; k < filterLength; ++k)
                w[k] += stepSize * error * h[k];

            data[n] = error; // output the noise-reduced signal
        }
    }
}
