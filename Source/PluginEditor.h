/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class TheMeadowlarkAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    TheMeadowlarkAudioProcessorEditor (TheMeadowlarkAudioProcessor&);
    ~TheMeadowlarkAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
  
    TheMeadowlarkAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TheMeadowlarkAudioProcessorEditor)
};
