/*
  ==============================================================================

    birdGenerator.cpp
    Created: 4 Jun 2024 12:41:46pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#include "birdGenerator.h"

BirdGenerator::BirdGenerator() : mWaveGenerator(), mAmplitude(0.25), mFrequency(440.0), mIsActive(false), mPhase(0.0), mSampleRate(44100)
{
}

BirdGenerator::~BirdGenerator()
{
}

bool BirdGenerator::canPlaySound(juce::SynthesiserSound* sound)

{
    return dynamic_cast<BirdSound*>(sound) != nullptr;
}

void BirdGenerator::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    mFrequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    mAmplitude = velocity;
    mWaveGenerator.setFrequency(mFrequency, mSampleRate);
    mIsActive = true;
    
    std::cout << "midi note: " << midiNoteNumber << " freq: " << mFrequency << std::endl;
}

void BirdGenerator::stopNote(float velocity, bool allowTailOff)
{
    clearCurrentNote();
    mIsActive = false;
}

void BirdGenerator::pitchWheelMoved(int newPitchWheelValue)
{
}

void BirdGenerator::controllerMoved(int controllerNumber, int newControllerValue)
{
}

void BirdGenerator::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    if (!mIsActive)
        return;
    
    float* leftChannelData = outputBuffer.getWritePointer(0, startSample);
    float* rightChannelData = outputBuffer.getWritePointer(1, startSample);
    
    for (int sample = 0; sample < numSamples; ++sample)
    {
        leftChannelData[sample] = mWaveGenerator.getNextSample() * mAmplitude;
        rightChannelData[sample] = mWaveGenerator.getNextSample() * mAmplitude;
    }
}








