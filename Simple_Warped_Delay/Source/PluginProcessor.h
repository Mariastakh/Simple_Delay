/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once
#include "maximilian.h"
#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/**
*/
class Simple_warped_delayAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    Simple_warped_delayAudioProcessor();
    ~Simple_warped_delayAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	// Tree state:
	AudioProcessorValueTreeState& getState();

private:
    //==============================================================================
	// Tree stuff:
	ScopedPointer<AudioProcessorValueTreeState> state;

	maxiOsc osc1, osc2, osc3;
	vector<double> currentBuffer, oldBuffer;
	maxiSample sample1, sample2;
	int counter = 0;
	int bufferIndex;
	int numSamples;
	float numSeconds;
	float dlout;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Simple_warped_delayAudioProcessor)
};
