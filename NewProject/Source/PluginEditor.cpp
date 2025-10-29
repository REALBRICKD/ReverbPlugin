/*
  ==============================================================================

    UI functionality

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
// Initialize UI elements of plugin, including sliders and labels.
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (650, 400);

    auto setupSlider = [](juce::Slider& s)
    {
        s.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        s.setTextBoxStyle(juce::Slider::TextBoxBelow, /*isReadOnly=*/false, 80, 24);
        s.setRange(0.0, 1.0, 0.001); // match APVTS parameter range
        s.setValue(0.5);
        s.setNumDecimalPlacesToDisplay(3);
    };

	// Initialize sliders, TODO: make helper method
    setupSlider(wetSlider);
    wetSlider.setBounds(50, 50, 100, 300);
    addAndMakeVisible(wetSlider);
	wetLabel.setText("Dry/Wet", juce::dontSendNotification);
	wetLabel.attachToComponent(&wetSlider, false);
	addAndMakeVisible(wetLabel);

    setupSlider(roomSizeSlider);
    roomSizeSlider.setBounds(200, 50, 100, 300);
    addAndMakeVisible(roomSizeSlider);
    roomSizeLabel.setText("Room Size", juce::dontSendNotification);
    roomSizeLabel.attachToComponent(&roomSizeSlider, false);
    addAndMakeVisible(roomSizeLabel);

    setupSlider(dampingSlider);
    dampingSlider.setBounds(350, 50, 100, 300);
    addAndMakeVisible(dampingSlider);
    dampingLabel.setText("Damping", juce::dontSendNotification);
    dampingLabel.attachToComponent(&dampingSlider, false);
    addAndMakeVisible(dampingLabel);

    setupSlider(widthSlider);
    widthSlider.setBounds(500, 50, 100, 300);
    addAndMakeVisible(widthSlider);
    widthLabel.setText("Width", juce::dontSendNotification);
    widthLabel.attachToComponent(&widthSlider, false);
    addAndMakeVisible(widthLabel);
	
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
    // Fill background
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

// Allow resizing support
void NewProjectAudioProcessorEditor::resized()
{
    wetSlider.setBounds(getLocalBounds());
	roomSizeSlider.setBounds(getLocalBounds());
	dampingSlider.setBounds(getLocalBounds());
	widthSlider.setBounds(getLocalBounds());
}
