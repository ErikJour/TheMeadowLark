/*
  ==============================================================================

    sequencer.h
    Created: 7 Jun 2024 9:15:47pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <vector>

class Sequencer

{
public:
    Sequencer();
    ~Sequencer();
    
    void init(double sampleRate, double sequenceDurationInSeconds);
    
private:
    
    int mCircularBufferLength;
    int mWritePosition;
    int mReadPosition;
};
