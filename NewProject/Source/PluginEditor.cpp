/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (650, 400);

    auto setupSlider = [](juce::Slider& s)
    {
        s.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        s.setTextBoxStyle(juce::Slider::TextBoxBelow, /*isReadOnly=*/false, 80, 24);
        s.setRange(0.0, 1.0, 0.001); // match APVTS parameter range
        s.setValue(0.5);
        s.setNumDecimalPlacesToDisplay(3);
    };

    setupSlider(wetSlider);
    wetSlider.setBounds(50, 50, 100, 300);
    addAndMakeVisible(wetSlider);

    setupSlider(roomSizeSlider);
    roomSizeSlider.setBounds(200, 50, 100, 300);
    addAndMakeVisible(roomSizeSlider);

    setupSlider(dampingSlider);
    dampingSlider.setBounds(350, 50, 100, 300);
    addAndMakeVisible(dampingSlider);

    setupSlider(widthSlider);
    widthSlider.setBounds(500, 50, 100, 300);
    addAndMakeVisible(widthSlider);


    // Create attachments that bind sliders to parameter IDs declared in createParameterLayout()
    wetAttachment      = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "Dry/Wet", wetSlider);
    roomSizeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "Room Size", roomSizeSlider);
    dampingAttachment  = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "Damping", dampingSlider);
    widthAttachment    = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "Width", widthSlider);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void NewProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    wetSlider.setBounds(getLocalBounds());
}