/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

using AudioGraphIOProcessor = AudioProcessorGraph::AudioGraphIOProcessor;
using Node = AudioProcessorGraph::Node;

//==============================================================================
/**
*/
class FilterAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    FilterAudioProcessor();
    ~FilterAudioProcessor();

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
        
    dsp::ProcessSpec setUpSpec(double sampleRate, int samplesPerBlock);
    
    AudioProcessorValueTreeState tree; //Link between Slider Value and Value in Audio
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterAudioProcessor)
    
    float lastSampleRate;
    
    std::unique_ptr<AudioProcessorGraph> mainProcessor;
    
    void updateGraph();

    Node::Ptr audioInputNode;
    Node::Ptr audioOutputNode;
    Node::Ptr midiInputNode;
    Node::Ptr midiOutputNode;
    
    void initialiseGraph();
    void connectAudioNodes();
    void connectMidiNodes();
    
    AudioParameterFloat* slot1Cutoff;
    AudioParameterFloat* slot1Resonance;
    
    AudioParameterFloat* slot2Cutoff;
    AudioParameterFloat* slot2Resonance;

    StringArray processorChoices { "Empty", "Highpass", "Lowpass"};
    
    AudioParameterBool* muteInput;
    AudioParameterChoice* processorSlot1;
    AudioParameterChoice* processorSlot2;
    
    Node::Ptr slot1Node;
    Node::Ptr slot2Node;
};

class FilterProcessor  : public FilterAudioProcessor
{
public:
    FilterProcessor() {}
    
    void prepareToPlay (double sampleRate, int samplesPerBlock) override
    {
        *filter.state = *dsp::IIR::Coefficients<float>::makeHighPass (sampleRate, 1000.0f);
        
        dsp::ProcessSpec spec { sampleRate, static_cast<uint32> (samplesPerBlock), 2 };
        filter.prepare (spec);
    }
    
    void processBlock (AudioSampleBuffer& buffer, MidiBuffer&) override
    {
        dsp::AudioBlock<float> block (buffer);
        dsp::ProcessContextReplacing<float> context (block);
        filter.process (context);
    }
    
    void reset() override
    {
        filter.reset();
    }
    
    const String getName() const override { return "Filter"; }
    
private:
    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> filter;
};

