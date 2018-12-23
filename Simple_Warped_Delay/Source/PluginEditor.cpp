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
	phasorFreq->setColour(Slider::textBoxTextColourId, Colours::black);
	phasorFreq->setLookAndFeel(&otherLookAndFeel);

	phasorFreqValue = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "PhasorFrequency", *phasorFreq);

  // Possible to add the phasor start position as a controllable parameter, but tends to confuse things:
	/*addAndMakeVisible(phasorStart = new Slider("phasorStart"));
	phasorStart->setSliderStyle(Slider::SliderStyle::Rotary);
	phasorStart->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
	phasorStart->setColour(Slider::textBoxTextColourId, Colours::black);
	phasorStart->setLookAndFeel(&otherLookAndFeel);

	phasorStartValue = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "PhasorSetStart", *phasorStart);
	*/
	addAndMakeVisible(phasorDur = new Slider("PhasorDur"));
	phasorDur->setSliderStyle(Slider::SliderStyle::Rotary);
	phasorDur->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
	phasorDur->setColour(Slider::textBoxTextColourId, Colours::black);
	phasorDur->setLookAndFeel(&otherLookAndFeel);

	phasorDurationValue = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "PhasorDuration", *phasorDur);

	addAndMakeVisible(setSamplesDial = new Slider("Samples"));
	setSamplesDial->setSliderStyle(Slider::SliderStyle::Rotary);
	setSamplesDial->setTextBoxStyle(Slider::TextBoxBelow, false, 100, 20);
	setSamplesDial->setColour(Slider::textBoxTextColourId, Colours::black);
	setSamplesDial->setLookAndFeel(&otherLookAndFeel);

	setSampleDuration = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "setSampleDuration", *setSamplesDial);

	addAndMakeVisible(phasorFreqLabel = new Label("Phasor Frequency Label"));
	phasorFreqLabel->setText("Frequency", dontSendNotification);
	phasorFreqLabel->setColour(Label::textColourId, Colours::peru);
	phasorFreqLabel->setFont(Font(16.0f, Font::bold));


	addAndMakeVisible(phasorDurationLabel = new Label("Phasor Duration Label"));
	phasorDurationLabel->setText("Duration", dontSendNotification);
	phasorDurationLabel->setColour(Label::textColourId, Colours::peru);

	addAndMakeVisible(setSamplesLabel = new Label("Sample Buffer Label"));
	setSamplesLabel->setText("Buffer Size", dontSendNotification);
	setSamplesLabel->setColour(Label::textColourId, Colours::peru);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (420, 300);
}

Simple_warped_delayAudioProcessorEditor::~Simple_warped_delayAudioProcessorEditor()
{
}

//==============================================================================
void Simple_warped_delayAudioProcessorEditor::paint (Graphics& g)
{
	g.fillAll(Colours::whitesmoke);
}

void Simple_warped_delayAudioProcessorEditor::resized()
{
	phasorFreq->setBounds(10, 10, 100, 100);
	phasorFreqLabel->setBounds(25, 115, 70, 30);

	phasorDur->setBounds(110, 10, 100, 100);
	phasorDurationLabel->setBounds(125, 115, 70, 30);

	setSamplesDial->setBounds(210, 10, 100, 100);
	setSamplesLabel->setBounds(225, 115, 70, 30);

	//phasorStart->setBounds(310, 10, 100, 100);
	//setSamplesLabel->setBounds(225, 115, 70, 30);
}
