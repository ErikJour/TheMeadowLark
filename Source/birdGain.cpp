/*
  ==============================================================================

    birdGain.cpp
    Created: 25 Jun 2024 6:40:49am
    Author:  Erik Jourgensen

  ==============================================================================
*/

#include "birdGain.h"

BirdGain::BirdGain() : gain(1.0f)
{
}

BirdGain::~BirdGain()
{
}

void BirdGain::setGain(float newGain)
{
    //Map values of 0 - 1 to a target value that corresponds to decibels
    
    gain = juce::jmap(newGain, 0.0f, 1.0f, -24.0f, 24.0f);
    
    //Convert this target value into decibels
    
    gain = juce::Decibels::decibelsToGain(gain, -24.0f);
}

float BirdGain::getGain() const
{
    return gain;
}

void BirdGain::process(float* inAudio, float* outAudio, int numSamplesToRender)
{
    
    //Apply Gain to Each Sample
    
    for (int i = 0; i < numSamplesToRender; ++i)
    {
        outAudio[i] = inAudio[i] * gain;
    }
}







