/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once
//#include "maximilian.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Simple_warped_delayAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    Simple_warped_delayAudioProcessorEditor (Simple_warped_delayAudioProcessor&);
    ~Simple_warped_delayAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    
    //// Sliders:
    ScopedPointer<Slider> phasorFreq;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> phasorFreqValue;
    
    ScopedPointer<Slider> phasorDuration;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> phasorDurationValue;
    
    ScopedPointer<Label> phasorFreqLabel;
    ScopedPointer<Label> phasorDurationLabel;
   
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Simple_warped_delayAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Simple_warped_delayAudioProcessorEditor)
    
    
};
