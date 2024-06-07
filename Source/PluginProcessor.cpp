/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TheMeadowlarkAudioProcessor::TheMeadowlarkAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    mBird.clearVoices();
    
    for (int voice = 0; voice < 2; ++voice)
    {
        mBird.addVoice (new BirdGenerator());
    }
    
    mBird.clearSounds();
    mBird.addSound(new BirdSound());
}

TheMeadowlarkAudioProcessor::~TheMeadowlarkAudioProcessor()
{
}

//==============================================================================
const juce::String TheMeadowlarkAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TheMeadowlarkAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TheMeadowlarkAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TheMeadowlarkAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TheMeadowlarkAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TheMeadowlarkAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TheMeadowlarkAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TheMeadowlarkAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String TheMeadowlarkAudioProcessor::getProgramName (int index)
{
    return {};
}

void TheMeadowlarkAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void TheMeadowlarkAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{

    mCurrentSampleRate = sampleRate;
    mBird.setCurrentPlaybackSampleRate(sampleRate);
    
    for (int i = 0; i < mBird.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<BirdGenerator*>(mBird.getVoice(i)))
        {
            voice->setCurrentPlaybackSampleRate(sampleRate);
        }
    }
    
}

void TheMeadowlarkAudioProcessor::releaseResources()
{

}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TheMeadowlarkAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void TheMeadowlarkAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    
    buffer.clear();
    
    juce::ScopedNoDenormals noDenormals;
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = 0; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    mBird.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool TheMeadowlarkAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* TheMeadowlarkAudioProcessor::createEditor()
{
    return new TheMeadowlarkAudioProcessorEditor (*this);
}

//==============================================================================
void TheMeadowlarkAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{

}

void TheMeadowlarkAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
 
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TheMeadowlarkAudioProcessor();
}
