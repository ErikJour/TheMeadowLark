/*
  ==============================================================================

    highPassFilter.h
    Created: 4 Jun 2024 12:43:06pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class HighPass

{
public:
    HighPass();
    ~HighPass();

    void setSampleRate(double sampleRate);
    void reset();
    void setHighPassFilterParams(double cutoffFrequency, double resonance);
    void process(juce::AudioBuffer<float>& buffer);
    double getLowCutFreq() const { return mHighPassFreq; }
    double getResonance() const { return mResonance; }
    
private:
    
    double mSampleRate;
    double mHighPassFreq;
    double mResonance;
    float  mBuffer;

    std::vector<juce::IIRFilter> filters;
};
