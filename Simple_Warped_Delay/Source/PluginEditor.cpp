/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Simple_warped_delayAudioProcessorEditor::Simple_warped_delayAudioProcessorEditor (Simple_warped_delayAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    
    addAndMakeVisible(phasorFreq = new Slider("PhasorFreq"));
    phasorFreq->setSliderStyle(Slider::SliderStyle::Rotary);
    phasorFreq->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
    
    phasorFreqValue = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "PhasorFrequency", *phasorFreq);
    
    addAndMakeVisible(phasorDuration = new Slider("PhasorDur"));
    phasorDuration->setSliderStyle(Slider::SliderStyle::Rotary);
    phasorDuration->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
    
    phasorDurationValue = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "PhasorDuration", *phasorDuration);
    
    addAndMakeVisible(phasorFreqLabel = new Label("Phasor Frequency Label"));
    phasorFreqLabel->setText("Frequency", dontSendNotification);
    phasorFreqLabel->setColour(Label::textColourId, Colours::red);
    
    addAndMakeVisible(phasorDurationLabel = new Label("Phasor Duration Label"));
    phasorDurationLabel->setText("Duration", dontSendNotification);
    phasorDurationLabel->setColour(Label::textColourId, Colours::red);
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

Simple_warped_delayAudioProcessorEditor::~Simple_warped_delayAudioProcessorEditor()
{
}

//==============================================================================
void Simple_warped_delayAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void Simple_warped_delayAudioProcessorEditor::resized()
{
    phasorFreq->setBounds( 10, 10, 100, 100);
    phasorFreqLabel->setBounds(25, 115, 70, 30);
    
    phasorDuration->setBounds( 110, 10, 100, 100);
    phasorDurationLabel->setBounds(125, 115,70, 30);
}
