/*
  ==============================================================================

    birdSound.h
    Created: 4 Jun 2024 1:53:24pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class BirdSound : public juce::SynthesiserSound
{
public:
    
    BirdSound();
    ~BirdSound();
    
    bool appliesToNote(int /*midiNoteNumber*/) override;
    bool appliesToChannel (int /*midiChannel*/) override;

};
