/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor. 
	The main code functionality is here.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessor::NewProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

NewProjectAudioProcessor::~NewProjectAudioProcessor()
{
}

//==============================================================================
const juce::String NewProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NewProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NewProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NewProjectAudioProcessor::getNumPrograms()
{
    return 1;  
}

int NewProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NewProjectAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String NewProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void NewProjectAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void NewProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Plugin initialization
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
	spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = 1;

    leftReverb.prepare(spec);
	rightReverb.prepare(spec);
}

void NewProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NewProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void NewProjectAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // Clears any unused output channels to minimize feedback.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // Audio is split into buffers to be processed. This applies all the parameter values to the audio buffers.
    params.roomSize = *apvts.getRawParameterValue("Room Size");
    params.damping = *apvts.getRawParameterValue("Damping");
    params.width = *apvts.getRawParameterValue("Width");
    params.wetLevel = *apvts.getRawParameterValue("Dry/Wet");
    params.dryLevel = 1.0f - *apvts.getRawParameterValue("Dry/Wet");
    params.freezeMode = *apvts.getRawParameterValue("Freeze");

    leftReverb.setParameters(params);
    rightReverb.setParameters(params);

    juce::dsp::AudioBlock<float> block(buffer);

    auto leftBlock = block.getSingleChannelBlock(0);
    auto rightBlock = block.getSingleChannelBlock(1);

    juce::dsp::ProcessContextReplacing<float> leftContext(leftBlock);
    juce::dsp::ProcessContextReplacing<float> rightContext(rightBlock);

    leftReverb.process(leftContext);
    rightReverb.process(rightContext);
}

//==============================================================================
bool NewProjectAudioProcessor::hasEditor() const
{
    return true; 
}

juce::AudioProcessorEditor* NewProjectAudioProcessor::createEditor()
{
    return new NewProjectAudioProcessorEditor (*this);
}

//==============================================================================
void NewProjectAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
}

void NewProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NewProjectAudioProcessor();
}
// Initialize all the plugin framework parameters, specifying acceptable ranges for them to take.
juce::AudioProcessorValueTreeState::ParameterLayout
NewProjectAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add(std::make_unique<juce::AudioParameterFloat>("Room Size",
        "Room Size",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f, 1.0f),
        0.5f,
        juce::String(),
        juce::AudioProcessorParameter::genericParameter,
        [](float value, int) {
            if (value * 100 < 10.0f)
                return juce::String(value * 100, 0);
            else if (value * 100 < 100.0f)
                return juce::String(value * 100, 0);
            else
                return juce::String(value * 100, 0); },
        nullptr));

    layout.add(std::make_unique<juce::AudioParameterFloat>("Damping",
        "Damping",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f, 1.0f),
        0.5f,
        juce::String(),
        juce::AudioProcessorParameter::genericParameter,
        [](float value, int) {
            if (value * 100 < 10.0f)
                return juce::String(value * 100, 2);
            else if (value * 100 < 100.0f)
                return juce::String(value * 100, 1);
            else
                return juce::String(value * 100, 0); },
        nullptr));

    layout.add(std::make_unique<juce::AudioParameterFloat>("Width",
        "Width",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f, 1.0f),
        0.5f,
        juce::String(),
        juce::AudioProcessorParameter::genericParameter,
        [](float value, int) {
            if (value * 100 < 10.0f)
                return juce::String(value * 100, 2);
            else if (value * 100 < 100.0f)
                return juce::String(value * 100, 1);
            else
                return juce::String(value * 100, 0); },
        nullptr));

    layout.add(std::make_unique<juce::AudioParameterFloat>("Dry/Wet",
        "Dry/Wet",
        juce::NormalisableRange<float>(0.0f, 1.0f, 0.001f, 1.0f),
        0.5f,
        juce::String(),
        juce::AudioProcessorParameter::genericParameter,
        [](float value, int) {
            if (value * 100 < 10.0f)
                return juce::String(value * 100, 2);
            else if (value * 100 < 100.0f)
                return juce::String(value * 100, 1);
            else
                return juce::String(value * 100, 0); },
        nullptr));

    layout.add(std::make_unique<juce::AudioParameterBool>("Freeze", "Freeze", false));

    return layout;
}
