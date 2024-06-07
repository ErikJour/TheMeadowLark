/*
  ==============================================================================

    waveGenerator.cpp
    Created: 4 Jun 2024 12:42:06pm
    Author:  Erik Jourgensen

  ==============================================================================
*/
#include "waveGenerator.h"

WaveGenerator::WaveGenerator() : mPhase(0.0f), mIncrement(0.0f)
{
}

WaveGenerator::~WaveGenerator()
{
}

void WaveGenerator::setFrequency(float frequency, float sampleRate)
{
    mIncrement = frequency / sampleRate;
}

float WaveGenerator::getNextSample()
{
    float currentSample = 0;
    
    //Generate a sine wave
    currentSample = std::sin(mPhase * 2.0 * M_PI);
    
    mPhase += mIncrement;
    if (mPhase >= 1.0f)
        mPhase -= 1.0f;
    
    return currentSample;
}

