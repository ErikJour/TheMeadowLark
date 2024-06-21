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
    addAndMakeVisible(reverbMixSlider);
    
    
    //Speed Slider
    speedSlider.addListener(this);
    speedSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    speedSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(speedSlider);
    
    
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
    speedSlider.setColour(0x1001312, taliesinRed);

    //Button
    speedSlider.setColour( 0x1001300, taliesenSunRise);
    
    //Fill
    speedSlider.setColour(0x1001311, taliesenEverGreen);
    

}

void TheMeadowlarkAudioProcessorEditor::resized()
{
    onButton.setBounds(500, 25, 50, 50);
    onButton.setSize(75, 25);
    
    reverbMixSlider.setBounds(50, 25, 50, 50);
    reverbMixSlider.setSize(100, 100);
    
    speedSlider.setBounds(450, 275, 50, 50);
    speedSlider.setSize(100, 100);


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
        audioProcessor.reverbSliderValueChanged();
    }
    
    if (slider == &speedSlider)
    {
        audioProcessor.speedSliderValueChanged();
    }
}
