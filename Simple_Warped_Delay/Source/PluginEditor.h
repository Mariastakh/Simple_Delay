/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
// Look and Feel Class:
class OtherLookAndFeel : public LookAndFeel_V4
{
public:
	OtherLookAndFeel()
	{
		setColour(Slider::thumbColourId, Colours::darkslategrey); // 0x1001300
		setColour(Slider::backgroundColourId, Colours::blue); // 0x1001200, defined below
		setColour(Slider::rotarySliderFillColourId, Colours::lightseagreen); // covered values
		setColour(Slider::rotarySliderOutlineColourId, Colours::darkslategrey); // outline colour when not covered
	}

	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
	{
		// JUCE code:

		auto outline = slider.findColour(Slider::rotarySliderOutlineColourId);
		auto fill = slider.findColour(Slider::rotarySliderFillColourId);

		//auto bounds = Juce::Rectangle<int>(x, y, width, height).toFloat().reduced (10);
		auto radius = jmin(width, height) / 2.0f;
		auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
		float rad = radius * 0.5;
		auto lineW = jmin(8.0f, rad);
		auto arcRadius = radius - lineW * 0.5f;

		// my circle:
		float centreX = x + width * 0.5f;
		float centreY = y + height * 0.5f;
		float rx = centreX - radius;
		float ry = centreY - radius;
		float rw = radius * 2.0f;

		g.setColour(Colours::whitesmoke);
		g.fillEllipse(rx, ry, rw, rw);

		// my small circle:
		// draw a smaller filled circle:
		float rx2 = centreX - (radius / 2);
		float ry2 = centreY - (radius / 2);
		// fill:
		g.setColour(Colours::darkslategrey);
		g.fillEllipse(rx2, ry2, (rw / 2), (rw / 2));
		//

		Path backgroundArc;
		backgroundArc.addCentredArc(width / 2,
			height / 2,
			arcRadius,
			arcRadius,
			0.0f,
			rotaryStartAngle,
			rotaryEndAngle,
			true);

		g.setColour(outline);
		g.strokePath(backgroundArc, PathStrokeType(lineW, PathStrokeType::beveled, PathStrokeType::butt));

		if (slider.isEnabled())
		{
			Path valueArc;
			valueArc.addCentredArc(width / 2,
				height / 2,
				arcRadius / 1.1,
				arcRadius / 1.1,
				0.0f,
				rotaryStartAngle,
				toAngle,
				true);

			g.setColour(fill);
			g.strokePath(valueArc, PathStrokeType(15, PathStrokeType::beveled, PathStrokeType::butt));
		}

		if (slider.isEnabled())
		{
			Path valueArc;
			valueArc.addCentredArc(width / 2,
				height / 2,
				arcRadius / 1.5,
				arcRadius / 1.5,
				0.0f,
				rotaryStartAngle,
				toAngle,
				true);

			g.setColour(Colours::darkseagreen);
			g.strokePath(valueArc, PathStrokeType(10, PathStrokeType::beveled, PathStrokeType::butt));
		}

		//if (slider.isEnabled())
		//{
		Path valueArc;
		valueArc.addCentredArc(width / 2,
			height / 2,
			arcRadius / 2.0,
			arcRadius / 2.0,
			0.0f,
			rotaryStartAngle,
			rotaryEndAngle,
			true);

		g.setColour(fill);
		g.strokePath(valueArc, PathStrokeType(5, PathStrokeType::mitered, PathStrokeType::butt));
		//}

		// my dial:
		float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
		Path p;
		float pointerLength = radius * 0.53f;
		float pointerThickness = 10.0f;
		p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
		p.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));

		// fill the pointer path:
		g.setColour(Colours::darkslategrey);
		g.fillPath(p);

	}
};

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

	//ScopedPointer<Slider> phasorStart;
	//ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> phasorStartValue;

	ScopedPointer<Slider> phasorDur;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> phasorDurationValue;

	ScopedPointer<Slider> setSamplesDial;
	ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> setSampleDuration;


	ScopedPointer<Label> phasorFreqLabel;
	ScopedPointer<Label> phasorDurationLabel;
	ScopedPointer<Label> setSamplesLabel;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Simple_warped_delayAudioProcessor& processor;
	OtherLookAndFeel otherLookAndFeel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Simple_warped_delayAudioProcessorEditor)
};
