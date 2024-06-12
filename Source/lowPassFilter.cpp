/*
  ==============================================================================

    lowPassFilter.cpp
    Created: 4 Jun 2024 12:43:13pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#include "lowPassFilter.h"

LowPass::LowPass()
    : mSampleRate(44100.0),
      mLowPassFreq(20.0),
      mResonance(0.1)
{
}
LowPass::~LowPass()
{
}
void LowPass::setSampleRate(double sampleRate)
{
    mSampleRate = sampleRate;
    filters.clear();
}
void LowPass::reset()
{
    
}
void LowPass::setLowPassFilterParams(double cutoffFrequency, double resonance)
{
    if (cutoffFrequency > 0.0 && cutoffFrequency <= mSampleRate * 0.5 && resonance > 0.0)
    {
        mLowPassFreq = cutoffFrequency;
        mResonance = resonance;

        juce::IIRCoefficients coefficients = juce::IIRCoefficients::makeLowPass(mSampleRate, mLowPassFreq, mResonance);
        
        filters.clear();
        filters.resize(2);
        for (auto& filter : filters)
        {
            filter.setCoefficients(coefficients);
        }
    }
}

void LowPass::process(juce::AudioBuffer<float>& buffer)
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
