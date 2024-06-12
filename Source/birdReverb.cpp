/*
  ==============================================================================

    birdReverb.cpp
    Created: 7 Jun 2024 8:37:27pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#include "birdReverb.h"

Reverb::Reverb() = default;

Reverb::~Reverb() = default;

void Reverb::setSampleRate (double sampleRate)
{
    reverb.setSampleRate(sampleRate);
}

void Reverb::setParameters(float dryLevel, float wetLevel)
{
    reverbParameters.dryLevel = dryLevel;
    reverbParameters.wetLevel = wetLevel;
}
