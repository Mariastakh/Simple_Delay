/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Simple_warped_delayAudioProcessor::Simple_warped_delayAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	// Tree stuff:
	state = new AudioProcessorValueTreeState(*this, nullptr);
	state->createAndAddParameter("PhasorFrequency", "PhasorFreq", "PhasorFreq", NormalisableRange<float>(1.0f, 10.0f, 0.001f), 1.0, nullptr, nullptr);
	state->createAndAddParameter("PhasorDuration", "PhasorDur", "PhasorDur", NormalisableRange<float>(5000.0f, 22050.0f, 1.0f), 5000.0, nullptr, nullptr); // doesnt like th 5000.0f
	state->createAndAddParameter("setSampleDuration", "Samples", "Samples", NormalisableRange<float>(1000.0f, 80000.0f, 1.0f), 1000.0, nullptr, nullptr);
	state->createAndAddParameter("setSwitch", "SwitchSlider", "SwitchSlider", NormalisableRange<float>(1.0f, 2.0f, 1.0f), 1.0, nullptr, nullptr);

	state->state = ValueTree("PhasorFrequency");
	state->state = ValueTree("PhasorDuration");
	state->state = ValueTree("setSampleDuration");
	state->state = ValueTree("setSwitch");

	numSeconds = 5.0; // need to be able to vary this. also the max Duration of the phasor will be determined by the storage buffer size
	numSamples = numSeconds * 44100;
	//desiredSamples = numSamples;
	oldBuffer.resize(numSamples);

	for (int i = 0; i < numSamples; i++)
	{
		oldBuffer[i] = 0;
	}

}

Simple_warped_delayAudioProcessor::~Simple_warped_delayAudioProcessor()
{
}

//==============================================================================
const String Simple_warped_delayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Simple_warped_delayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Simple_warped_delayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Simple_warped_delayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Simple_warped_delayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Simple_warped_delayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Simple_warped_delayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Simple_warped_delayAudioProcessor::setCurrentProgram (int index)
{
}

const String Simple_warped_delayAudioProcessor::getProgramName (int index)
{
    return {};
}

void Simple_warped_delayAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Simple_warped_delayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Simple_warped_delayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Simple_warped_delayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void Simple_warped_delayAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();

	// Get incoming Daw samples from buffer:
	auto* channelData0 = buffer.getReadPointer(0);
	auto* channelData1 = buffer.getReadPointer(1);

	// Get write pointer to buffer:
	auto* outputChannelData0 = buffer.getWritePointer(0);
	auto* outputChannelData1 = buffer.getWritePointer(1);

	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());
    
	// Grab values from the sliders:
	float phasorFreq = *state->getRawParameterValue("PhasorFrequency");
	float phasorDuration = *state->getRawParameterValue("PhasorDuration");
	float desiredSamples = *state->getRawParameterValue("setSampleDuration");
	//==========
	
	// This slider allows us to switch between the normal single-tap delay mode,
	// and a version of the code where the delay line (oldBuffer) is read
	// from at a range of indexes set by a phasor with changeable frequency
	// and endPhase parameters. 
	// This results in a delay which repeats the same segment in the delay buffer
	// until the user changes the parameters. The frequency of 
	// the phasor (the speed with which the index increments) influences the
	// pitch of the playback. 
	int garble = *state->getRawParameterValue("setSwitch");
	
	for (int sample = 0; sample < buffer.getNumSamples(); sample++)
	{
	    
		// acquire the dry signal:
		double dryLeft = buffer.getReadPointer(0)[sample];

		// THE DELAY CODE:
		double out;
		if (garble == 1)
		{
		    // grab value from the storage buffer:
			 out = oldBuffer[counter];
			 resetPhase = true;
			 
		} else if(garble ==2){
            // Reset phase if the slider has just been toggled;
		    if(resetPhase == true) osc1.phaseReset(0);
		    // set the index via the phasor value:
		    int index = osc1.phasor(phasorFreq, 0, phasorDuration);
		    // grab value from the storage buffer
			out = oldBuffer[index]; //
			resetPhase = false;
		}
		
        // Set the current buffer index to the new dry signal mixed with
        // a bit of the old: that's it!
		oldBuffer[counter] = dryLeft + (out * 0.5);

		// This decides the delaytime, which is the amount of 
		// samples between the current signal, and the delayed version
		// stored in the buffer:
		counter++;
		if (counter >= desiredSamples) //numSamples
		{
			counter = 0;
		}

		// OUTPUT:
		*outputChannelData0 = out;
		*outputChannelData1 = out;
    
		// Increment thru DAW buffer:
		outputChannelData0++;
		outputChannelData1++;

	}

}

//========
AudioProcessorValueTreeState& Simple_warped_delayAudioProcessor::getState()
{
	// returns reference to state
	return *state;
}

//==============================================================================
bool Simple_warped_delayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Simple_warped_delayAudioProcessor::createEditor()
{
    return new Simple_warped_delayAudioProcessorEditor (*this);
}

//==============================================================================
void Simple_warped_delayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Simple_warped_delayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Simple_warped_delayAudioProcessor();
}
