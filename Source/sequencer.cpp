/*
  ==============================================================================

    sequencer.cpp
    Created: 7 Jun 2024 9:15:47pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#include "sequencer.h"


Sequencer::Sequencer()
{
}
Sequencer::~Sequencer()
{
    
}
    
void Sequencer::init(double sampleRate, double sequenceDurationInSeconds)
{
    mCircularBufferLength = sampleRate * sequenceDurationInSeconds/*replace with Speed                                                                  parameter*/;
    
    mWritePosition = 0;
    mReadPosition = 0;
}

///*void Sequencer::addSound*/(midiMessage, position, sampleRate)
//                          {
//                          }
    


