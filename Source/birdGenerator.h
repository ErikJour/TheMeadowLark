/*
  ==============================================================================

    birdGenerator.h
    Created: 4 Jun 2024 12:41:46pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "waveGenerator.h"
#include "birdSound.h"
#include "lowPassFilter.h"





class BirdGenerator : public juce::SynthesiserVoice
{
public:
    BirdGenerator();
    ~BirdGenerator();
    
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void setADSRSampleRate (double sampleRate);
    void getEnvelopeParams(float attack, float release);
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
  
    
private:
    WaveGenerator mWaveGenerator;
    
    double mAmplitude;
    double mFrequency;
    bool mIsActive;
    double mPhase;
    double mSampleRate;
    
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;
    
};
