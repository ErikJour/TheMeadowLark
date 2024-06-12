/*
  ==============================================================================

    lowPassFilter.h
    Created: 4 Jun 2024 12:43:13pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class LowPass

{
public:
    LowPass();
    ~LowPass();

    void setSampleRate(double sampleRate);
    void reset();
    void setLowPassFilterParams(double cutoffFrequency, double resonance);
    void process(juce::AudioBuffer<float>& buffer);
    double getLowCutFreq() const { return mLowPassFreq; }
    double getResonance() const { return mResonance; }
    
private:
    
    double mSampleRate;
    double mLowPassFreq;
    double mResonance;
    float  mBuffer;

    std::vector<juce::IIRFilter> filters;
};
