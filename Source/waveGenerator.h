/*
  ==============================================================================

    waveGenerator.h
    Created: 4 Jun 2024 12:42:06pm
    Author:  Erik Jourgensen

  ==============================================================================
*/
#pragma once
#include "JuceHeader.h"

class WaveGenerator

{
public:
    
    WaveGenerator();
    ~WaveGenerator();
    
    void setFrequency(float frequency, float sampleRate);
    float getNextSample();
    
   
private:
    
    double mPhase;
    double mIncrement;
};
