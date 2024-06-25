/*
  ==============================================================================

    sequencer.cpp
    Created: 7 Jun 2024 9:15:47pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#include "sequencer.h"



Sequencer::Sequencer() : mCircularBufferLeft (nullptr), mCircularBufferRight (nullptr), mWritePosition(0), mReadPosition(0)
{
}
Sequencer::~Sequencer()
{
    //If circular buffer has memory allocated, clear it
    
    if (mCircularBufferLeft != nullptr)
    {
        delete [] mCircularBufferLeft;
        mCircularBufferLeft = nullptr;
    }
    
    if (mCircularBufferRight != nullptr)
    {
        delete [] mCircularBufferRight;
        mCircularBufferRight = nullptr;
    }
    
}
    
void Sequencer::init(double sampleRate)
{
    
    //If circular buffer is a nullptr, allocate an array of floats and make  the size is an integer
    
    if (mCircularBufferLeft == nullptr)
    {
        mCircularBufferLeft = new float [(int) (sampleRate * MAX_BUFFER_TIME)];
    }
    
    if (mCircularBufferRight == nullptr)
    {
        mCircularBufferRight = new float [(int) (sampleRate * MAX_BUFFER_TIME)];
    }
    
    // Write and Read positions
    
    mWritePosition = 0;
    
    mReadPosition = 0;
}

//Methods to be called by birdGenerator

void Sequencer::updateParameters(float* updateCircularBufferLeft, float* updateCircularBufferRight)
{
    mCircularBufferLeft = updateCircularBufferLeft;
    mCircularBufferRight = updateCircularBufferRight;
}

void Sequencer::updateWriteHead(int newWriteHeadPosition){
    
    mWritePosition = newWriteHeadPosition;
}

void Sequencer::getReadHead(float newReadHead){
    
    mReadPosition = newReadHead;
}



