/*
  ==============================================================================

    birdSound.cpp
    Created: 4 Jun 2024 1:53:24pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#include "birdSound.h"

BirdSound::BirdSound()
{
    
}

BirdSound::~BirdSound()
{
    
}

bool BirdSound::appliesToNote(int /*midiNoteNumber*/)
{
    return true;
}

bool BirdSound::appliesToChannel (int /*midiChannel*/)
{
    return true;
}
