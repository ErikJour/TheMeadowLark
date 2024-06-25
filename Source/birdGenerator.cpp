/*
  ==============================================================================

    birdGenerator.cpp
    Created: 4 Jun 2024 12:41:46pm
    Author:  Erik Jourgensen

  ==============================================================================
*/

#include "birdGenerator.h"

BirdGenerator::BirdGenerator() : mWaveGenerator(), mFrequency(440.0), mIsActive(false), mPhase(0.0), mSampleRate(44100), adsr(), writeHeadPosition(0), circularBufferTime(static_cast<int>(mSampleRate * MAX_BUFFER_TIME)), readHeadPosition(0), mAmplitude(0.25)
{
    // Initialize Envelope Parameters
    
    getEnvelopeParams(1.0f, 0.5f);
    
    //Dynamically Allocate Memory in Circular Buffer - MOVE THIS

    newCircularBufferLeft = new float[circularBufferTime]();
    newCircularBufferRight = new float[circularBufferTime]();
    
    //Initialize Sequencer Parameters
    
    sequencer.init(mSampleRate);
    sequencer.updateWriteHead(writeHeadPosition);
    
    //Define Circular Buffer Time - MOVE THIS
    
    circularBufferTime = (int) mSampleRate * MAX_BUFFER_TIME;
    
    readHeadPosition = 0;
    
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

void BirdGenerator::setSeqeuncerSampleRate(double sampleRate)
{
    sequencer.init(sampleRate);
}

void BirdGenerator::getEnvelopeParams(float attack, float release)
{
    adsrParams.attack = 0.2;
    adsrParams.decay = 0.3;
    adsrParams.sustain = 0.0;
    adsrParams.release = 0.1;
    adsr.setParameters(adsrParams);
}

void BirdGenerator::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
        
    adsr.reset();
    adsr.setParameters(adsrParams);
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

void BirdGenerator::initDistance()
{
    distance.reset();
    distance.setSampleRate(mSampleRate);
}


void BirdGenerator::setDistanceParameters()
{
    juce::Reverb::Parameters distanceParameters;
    distanceParameters.dryLevel = 0.0f;
    distanceParameters.wetLevel = 1.0f;
    distanceParameters.width = 0.5f;
    distanceParameters.roomSize = 1.0f;
  
 
}

void BirdGenerator::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    //Clear the Buffer -----------------------
    
    outputBuffer.clear();
        
    //Go Through the Samples in the Buffer -------------------------

    
    for (int sample = 0; sample < numSamples; ++sample)
    {
        
        if (mIsActive)
        {
            // Apply Sine Wave ------------------------------

            float currentSample =  mAmplitude * mWaveGenerator.getNextSample() *adsr.getNextSample();
            
            //Write into the current sample --------------------------------------------
            
            newCircularBufferLeft[writeHeadPosition] = currentSample;
            newCircularBufferRight[writeHeadPosition] = currentSample;
            
            //Readhead and writehead timing are synced;
            
            readHeadPosition = writeHeadPosition;
            
            //Start read head position
            
            if (readHeadPosition < 0)
            {
                readHeadPosition += circularBufferTime;
            }
            
            //Process channels
            
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                float* currentBuffer = (channel == 0) ? newCircularBufferLeft : newCircularBufferRight;
                
                float bufferSample = currentBuffer[readHeadPosition];
                
                outputBuffer.setSample(channel, startSample, bufferSample);
            }
        }
        
        //Increment write head position in the buffer ---------------------
        
        writeHeadPosition++;
        
        //Circle back to beginning of buffer ------------------------------
        
        if (writeHeadPosition >= circularBufferTime)
        {
            writeHeadPosition = 0;
        }
        
        
        //NOTES -------------------------------------------------------------
        
        //First Note
        
       if (writeHeadPosition == 7000)
        {
            adsrParams.attack = 0.6;
            adsrParams.decay = 0.01;
            adsrParams.release = 0.1;
            startNote(117, 22, nullptr, 0);
        }
        
        else if (writeHeadPosition == 7999)
        {
            
            stopNote(70, true);
        }
        
        //Second Note ------------------------------------------------------
        
        else if (writeHeadPosition == 8000)
        {
            adsrParams.attack = 0.2;
            adsrParams.decay = 0.01;
            adsrParams.release = 0.1;
            startNote(105, 10, nullptr, 0);
        }
        
        else if (writeHeadPosition == 8500)
        {
            
            stopNote(70, true);
        }
        
        // Third Note ----------------------------------------------------------
        
        else if (writeHeadPosition == 16000)
        {
            adsrParams.attack = 0.2;
            adsrParams.decay = 0.01;
            adsrParams.release = 0.1;
            startNote(112, 5, nullptr, 0);
        }
        
        else if (writeHeadPosition == 17000)
        {
            stopNote(70, true);
        }
        
        //Fourth Note --------------------------------------------------------------

        else if (writeHeadPosition == 19000)
        {
            adsrParams.attack = 0.2;
            adsrParams.decay = 1.0;
            adsrParams.release = 0.1;
            startNote(102, 43, nullptr, 0);
        }
        
        else if (writeHeadPosition == 20000)
        {
            stopNote(70, true);
        }
        
        //Fifth Note --------------------------------------------------------------
        
        else if (writeHeadPosition == 24000)
        {
            adsrParams.attack = 0.5;
            adsrParams.decay = 0.5;
            adsrParams.release = 0.2;
            startNote(99, 6, nullptr, 0);
        }
        
        else if (writeHeadPosition == 27000)
        {
            stopNote(70, true);
        }
        
        //Sixth Note --------------------------------------------------------------
        
        if (writeHeadPosition == 36000)
         {
             adsrParams.attack = 0.8;
             adsrParams.decay = 0.01;
             adsrParams.release = 0.1;
             startNote(117, 23, nullptr, 0);
         }
         
         else if (writeHeadPosition == 39000)
         {
             
             stopNote(70, true);
         }
        
        //Seventh Note -------------------------------------------------------------
        
        else if (writeHeadPosition == 215000)
        {
            adsrParams.attack = 0.1;
            adsrParams.decay = 0.01;
            adsrParams.release = 0.01;
            startNote(100, 2, nullptr, 0);
        }
        
        //Eighth Note -------------------------------------------------------------
        
        else if (writeHeadPosition == 222000)
        {
            adsrParams.attack = 0.4;
            adsrParams.decay = 0.01;
            adsrParams.release = 0.8;
            startNote(96, 1, nullptr, 0);
        }
        
        else if (writeHeadPosition == 225000)
        {
            stopNote(70, true);
        }
        startSample++;
    }
    
    //Tracking the write head position ------------------------------------------
    
    if (writeHeadPosition % 500 == 0){

        std::cout << "write head position " << writeHeadPosition << std::endl;
    }
}




