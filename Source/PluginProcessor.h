/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "birdSound.h"
#include "birdGenerator.h"
#include "birdReverb.h"
#include "lowPassFilter.h"
#include "highPassFilter.h"
#include "birdGain.h"



//==============================================================================
/**
*/
class TheMeadowlarkAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    TheMeadowlarkAudioProcessor();
    ~TheMeadowlarkAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void ifButtonDepressed();

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;
    void setDistanceParameters();

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void currentLowPassFreq (float updatedLowPassFreq);
    void sliderValueChanged();
    void lowPassSliderValueChanged();
    void setGain (float gainValue);
    
    double volume;
    BirdGenerator birdGenerator;

private:
        
    juce::Synthesiser mBird;
    
    double mCurrentSampleRate;
    
    bool buttonDepressed = true;
    
    Reverb reverb;
    
    LowPass lowPassFilter;
    
    HighPass highPassFilter;
    
    juce::Reverb distance;
    
    BirdGain birdGain;
    
   

    
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TheMeadowlarkAudioProcessor)
};
