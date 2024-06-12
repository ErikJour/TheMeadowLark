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
    //On Button
    onButton.addListener(this);
    addAndMakeVisible(onButton);
    
    //Distance Slider
    reverbMixSlider.addListener(this);
    addAndMakeVisible(reverbMixSlider);
    
    
    //Speed Slider
    speedSlider.addListener(this);
    addAndMakeVisible(speedSlider);
    
    
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
    onButton.setBounds(300, 50, 50, 50);
}

void TheMeadowlarkAudioProcessorEditor::buttonClicked (juce::Button* button)
{
    if (button == &onButton)
    {
        audioProcessor.ifButtonDepressed();
    }
}

void TheMeadowlarkAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &reverbMixSlider)
    {
        audioProcessor.reverbSliderValueChanged();
    }
    
    if (slider == &speedSlider)
    {
        audioProcessor.speedSliderValueChanged();
    }
}
