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

#define MAX_BUFFER_TIME 7

class Sequencer

{
public:
    Sequencer();
    ~Sequencer();
    
    void init(double sampleRate);
    void updateParameters (float* updateCircularBufferLeft, float* updateCircularBufferRight);
    void updateWriteHead (int newWriteHeadPosition);
    void getReadHead (float newReadHead);
    
private:
    
   float*  mCircularBufferLeft;
   float*  mCircularBufferRight;
    
    int mCircularBufferLength;
    int mWritePosition;
    float mReadPosition;
};
