/*
  ==============================================================================

    Plugin UI header.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class NewProjectAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    NewProjectAudioProcessorEditor (NewProjectAudioProcessor&);
    ~NewProjectAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //Create new audio processor
    NewProjectAudioProcessor& audioProcessor;

	//Initialize Sliders
    juce::Slider wetSlider;
    juce::Slider roomSizeSlider;
	juce::Slider dampingSlider;
    juce::Slider widthSlider;

    //Initialize Labels
    juce::Label wetLabel;
    juce::Label roomSizeLabel;
    juce::Label dampingLabel;
    juce::Label widthLabel;

    // Attachments bind GUI controls to APVTS parameters
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> wetAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> roomSizeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dampingAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> widthAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessorEditor)
};
