/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TheMeadowlarkAudioProcessorEditor::TheMeadowlarkAudioProcessorEditor (TheMeadowlarkAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
  
    setSize (400, 300);
}

TheMeadowlarkAudioProcessorEditor::~TheMeadowlarkAudioProcessorEditor()
{
}

//==============================================================================
void TheMeadowlarkAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("The Meadowlark", getLocalBounds(), juce::Justification::centred, 1);
}

void TheMeadowlarkAudioProcessorEditor::resized()
{

}
