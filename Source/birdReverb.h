/*
  ==============================================================================

    birdReverb.h
    Created: 7 Jun 2024 8:37:27pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class Reverb 

{
public:
    Reverb();
    ~Reverb();
    void setSampleRate (double sampleRate);
    void setParameters(float dryLevel, float wetLevel);
   
    
private:
    
    juce::Reverb reverb;
    
    juce::Reverb::Parameters reverbParameters;
    
};
