/*
  ==============================================================================

    highPassFilter.cpp
    Created: 4 Jun 2024 12:43:06pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#include "highPassFilter.h"

HighPass::HighPass()
    : mSampleRate(44100.0),
      mHighPassFreq(100.0),
      mResonance(0.1),
      filters()
{
}
HighPass::~HighPass()
{
}
void HighPass::setSampleRate(double sampleRate)
{
    mSampleRate = sampleRate;
}
void HighPass::reset()
{
    
}
void HighPass::setHighPassFilterParams(double cutoffFrequency, double resonance)
{
    mHighPassFreq = cutoffFrequency;
    juce::IIRCoefficients coefficients = juce::IIRCoefficients::makeHighPass(mSampleRate, mHighPassFreq, mResonance);
    
    filters.clear();
    filters.resize(2);
    
    for (auto& filter : filters)
    {
        filter.setCoefficients(coefficients);
    }
}

void HighPass::process(juce::AudioBuffer<float>& buffer)
{
    const int numChannels = buffer.getNumChannels();
    const int numSamples = buffer.getNumSamples();

    for (int channel = 0; channel < numChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);
        
    
        for (int sample = 0; sample < numSamples; ++sample)
        {
            channelData[sample] = static_cast<float>(filters[channel].processSingleSampleRaw(static_cast<double>(channelData[sample])));
        }
    }
}
