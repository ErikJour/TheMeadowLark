/*
  ==============================================================================

    birdGain.h
    Created: 25 Jun 2024 6:40:49am
    Author:  Erik Jourgensen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class BirdGain
{
public:
    BirdGain();
    ~BirdGain();

    void setGain(float newGain);
    float getGain() const;

    void process(float* inAudio, float* outAudio, int numSamplesToRender);

private:
    float gain;
};
