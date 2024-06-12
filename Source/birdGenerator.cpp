/*
  ==============================================================================

    birdGenerator.cpp
    Created: 4 Jun 2024 12:41:46pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#include "birdGenerator.h"

BirdGenerator::BirdGenerator() : mWaveGenerator(), mAmplitude(0.25), mFrequency(440.0), mIsActive(false), mPhase(0.0), mSampleRate(44100), adsr()
{
    getEnvelopeParams(1.0f, 0.5f);
}

BirdGenerator::~BirdGenerator()
{
}

bool BirdGenerator::canPlaySound(juce::SynthesiserSound* sound)

{
    return dynamic_cast<BirdSound*>(sound) != nullptr;
}

void BirdGenerator::setADSRSampleRate(double sampleRate)
{
    adsr.setSampleRate(sampleRate);
}

void BirdGenerator::getEnvelopeParams(float attack, float release)
{
    adsrParams.attack = 0.5;
    adsrParams.decay = 0.1;
    adsrParams.sustain = 0.1;
    adsrParams.release = 0.5;
    adsr.setParameters(adsrParams);
}
void BirdGenerator::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    adsr.reset();
    
    mFrequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    mAmplitude = velocity;
    mWaveGenerator.setFrequency(mFrequency, mSampleRate);
    mIsActive = true;
    
    adsr.noteOn();
    
    std::cout << "midi note: " << midiNoteNumber << " freq: " << mFrequency << std::endl;
}

void BirdGenerator::stopNote(float velocity, bool allowTailOff)
{
    adsr.noteOff();
    
    if (!allowTailOff || !adsr.isActive())
    {
        clearCurrentNote();
        mIsActive = false;
    }
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
    
    for (int sample = 0; sample < numSamples; ++sample)
    {
        float envelopeValue = adsr.getNextSample();
        float currentSample = envelopeValue * mWaveGenerator.getNextSample();
        
        for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
        {
            outputBuffer.addSample(channel, startSample, currentSample);
        }
        
        ++startSample;
    }
    
}






