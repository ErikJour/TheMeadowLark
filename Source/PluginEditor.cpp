/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TheMeadowlarkAudioProcessorEditor::TheMeadowlarkAudioProcessorEditor (TheMeadowlarkAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), isButtonOn (false)
{
    //On Button
    onButton.addListener(this);
    addAndMakeVisible(onButton);
    onButton.setButtonText("Off");
    juce::Colour taliesinGreen = juce::Colour::fromRGB(77, 119, 95);
    
    onButton.setColour(juce::TextButton::buttonColourId, taliesinGreen);

    
    //Distance Slider
    reverbMixSlider.addListener(this);
    reverbMixSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    reverbMixSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    reverbMixSlider.setRange(0.0f, 1.0f, 0.0001f);
    reverbMixSlider.setValue(0.5f);
    addAndMakeVisible(reverbMixSlider);
    
    //Distance Label
    juce::Colour taliesenSunRise = juce::Colour::fromRGB(255, 204, 102);

    distanceLabel.setText("Distance", juce::dontSendNotification);
    distanceLabel.attachToComponent(&reverbMixSlider, false);
    distanceLabel.setJustificationType(juce::Justification::centred);
    distanceLabel.setColour(juce::Label::textColourId, taliesenSunRise); 
    addAndMakeVisible(distanceLabel);
    
    
    //Volume Slider
    volumeSlider.addListener(this);
    volumeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    volumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    volumeSlider.setRange(0.0f, 1.0f, 0.0001f);
    volumeSlider.setValue(0.5f);
    addAndMakeVisible(volumeSlider);
    
    //Volume Label
    volumeLabel.setText("Volume", juce::dontSendNotification);
    volumeLabel.attachToComponent(&volumeSlider, false);
    volumeLabel.setJustificationType(juce::Justification::centred);
    volumeLabel.setColour(juce::Label::textColourId, taliesenSunRise);
    addAndMakeVisible(volumeLabel);
    
    
    setSize (600, 400);
}

TheMeadowlarkAudioProcessorEditor::~TheMeadowlarkAudioProcessorEditor()
{
}

//==============================================================================
void TheMeadowlarkAudioProcessorEditor::paint (juce::Graphics& g)
{
    juce::Colour taliesinGreen = juce::Colour::fromRGB(77, 119, 95);
    g.fillAll (taliesinGreen);
    
    juce::Image background = juce::ImageCache::getFromMemory (BinaryData::MeadowLark_Outline_V3_png, BinaryData::MeadowLark_Outline_V3_pngSize);
    g.drawImage(background, 0, 0, getWidth(), getHeight(), 0, 0, background.getWidth(), background.getHeight());
    juce::Colour taliesinRed = juce::Colour::fromRGB(204, 85, 0);
    juce::Colour taliesenEverGreen = juce::Colour::fromRGB(34, 139, 34);
    juce::Colour taliesenSunRise = juce::Colour::fromRGB(255, 204, 102);
    
    //Distance Slider--------------------------------------------------
    
    //Init Path
    reverbMixSlider.setColour(0x1001312, taliesinRed);

    //Button
    reverbMixSlider.setColour( 0x1001300, taliesenSunRise);
    
    //Fill
    reverbMixSlider.setColour(0x1001311, taliesenEverGreen);
    
    //Speed Slider------------------------------------------------------
    
    //Init Path
    volumeSlider.setColour(0x1001312, taliesinRed);

    //Button
    volumeSlider.setColour( 0x1001300, taliesenSunRise);
    
    //Fill
    volumeSlider.setColour(0x1001311, taliesenEverGreen);
    

}

void TheMeadowlarkAudioProcessorEditor::resized()
{
    onButton.setBounds(500, 25, 50, 50);
    onButton.setSize(75, 25);
    
    reverbMixSlider.setBounds(50, 25, 50, 50);
    reverbMixSlider.setSize(100, 100);
    
    volumeSlider.setBounds(450, 275, 50, 50);
    volumeSlider.setSize(100, 100);


}

void TheMeadowlarkAudioProcessorEditor::buttonClicked (juce::Button* button)
{
    if (button == &onButton)
    {
        isButtonOn = !isButtonOn;
        audioProcessor.ifButtonDepressed();
        
        if (isButtonOn)
                {
                    onButton.setButtonText("On");
                    juce::Colour taliesinRed = juce::Colour::fromRGB(204, 85, 0);
                    onButton.setColour(juce::TextButton::buttonColourId, taliesinRed);
//
                }
                else
                {
                    onButton.setButtonText("Off");
                    juce::Colour taliesinGreen = juce::Colour::fromRGB(77, 119, 95);
                    onButton.setColour(juce::TextButton::buttonColourId, taliesinGreen);
                }
        
        repaint();
    }
}

void TheMeadowlarkAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &reverbMixSlider)
    {
        audioProcessor.sliderValueChanged();
    }
    
    if (slider == &volumeSlider)
    {
        float gainValue = slider->getValue();
        audioProcessor.setGain(gainValue);
        
    }
}
float TheMeadowlarkAudioProcessorEditor::getDistanceSliderValue() const
{
    return reverbMixSlider.getValue();
}


