/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin processor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "LowPassFilterProcessor.h"
#include "HighPassFilterProcessor.h"

//==============================================================================
FilterAudioProcessor::FilterAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
: AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                  .withInput  ("Input",  AudioChannelSet::stereo(), true)
#endif
                  .withOutput ("Output", AudioChannelSet::stereo(), true)
#endif
                  )
, tree (*this, nullptr)
, mainProcessor  (new AudioProcessorGraph())
#endif
{
    NormalisableRange<float> cutoffRange (20.0f, 20000.0f);
    NormalisableRange<float> resRange (1.0f, 5.0f);
    
    NormalisableRange<float> boolRange (0.0f, 1.0f);
    NormalisableRange<float> choiceRange (0.0f,3.0f);
    
    tree.createAndAddParameter("slot1Cutoff", "Slot1Cutoff", "Slot1Cutoff", cutoffRange, 600.0f, nullptr, nullptr);
    tree.createAndAddParameter("slot1Resonance", "Slot1Resonance", "Slot1Resonance", resRange, 1.0f, nullptr, nullptr);
    
    tree.createAndAddParameter("slot2Cutoff", "Slot2Cutoff", "Slot2Cutoff", cutoffRange, 600.0f, nullptr, nullptr);
    tree.createAndAddParameter("slot2Resonance", "Slot2Resonance", "Slot2Resonance", resRange, 1.0f, nullptr, nullptr);
    
    tree.createAndAddParameter("slot1Mute", "Slot1Mute", "Slot1Mute", boolRange, 1.0f, nullptr, nullptr);
    tree.createAndAddParameter("slot2Mute", "Slot2Mute", "Slot2Mute", boolRange, 1.0f, nullptr, nullptr);
    
    tree.createAndAddParameter("processorSlot1", "ProcessorSlot1", "ProcessorSlot1", choiceRange, 0.0f, nullptr, nullptr);
    
    tree.createAndAddParameter("processorSlot2", "ProcessorSlot2", "ProcessorSlot2", choiceRange, 0.0f, nullptr, nullptr);
    
    tree.state = ValueTree("SynthTree");
}

FilterAudioProcessor::~FilterAudioProcessor()
{
}

//==============================================================================
const String FilterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FilterAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool FilterAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool FilterAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double FilterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FilterAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int FilterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FilterAudioProcessor::setCurrentProgram (int index)
{
}

const String FilterAudioProcessor::getProgramName (int index)
{
    return {};
}

void FilterAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void FilterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mainProcessor->setPlayConfigDetails (getMainBusNumInputChannels(),
                                         getMainBusNumOutputChannels(),
                                         sampleRate, samplesPerBlock);
    
    mainProcessor->prepareToPlay (sampleRate, samplesPerBlock);
    
    initialiseGraph();
}

void FilterAudioProcessor::initialiseGraph()
{
    mainProcessor->clear();
    audioInputNode  = mainProcessor->addNode (new AudioGraphIOProcessor (AudioGraphIOProcessor::audioInputNode));
    audioOutputNode = mainProcessor->addNode (new AudioGraphIOProcessor (AudioGraphIOProcessor::audioOutputNode));
    midiInputNode   = mainProcessor->addNode (new AudioGraphIOProcessor (AudioGraphIOProcessor::midiInputNode));
    midiOutputNode  = mainProcessor->addNode (new AudioGraphIOProcessor (AudioGraphIOProcessor::midiOutputNode));
    connectAudioNodes();
    connectMidiNodes();
}

void FilterAudioProcessor::connectAudioNodes()
{
    for (int channel = 0; channel < 2; ++channel)
        mainProcessor->addConnection (
                                      {
                                          { audioInputNode->nodeID,  channel },
                                          { audioOutputNode->nodeID, channel }
                                          
                                      });
}

void FilterAudioProcessor::connectMidiNodes()
{
    mainProcessor->addConnection (
                                  {
                                      { midiInputNode->nodeID,  AudioProcessorGraph::midiChannelIndex },
                                      { midiOutputNode->nodeID, AudioProcessorGraph::midiChannelIndex }
                                  });
}

dsp::ProcessSpec FilterAudioProcessor::setUpSpec(double sampleRate, int samplesPerBlock)
{
    dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumInputChannels();
    
    return spec;
}

void FilterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    mainProcessor->releaseResources();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FilterAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void FilterAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    for (auto i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    updateGraph();
}

void FilterAudioProcessor::updateGraph()
{
    bool hasChanged = false;
    float* processorSlot1Choice = tree.getRawParameterValue("processorSlot1");
    float* processorSlot2Choice = tree.getRawParameterValue("processorSlot2");
    
    Array<float*> choices { processorSlot1Choice,
        processorSlot2Choice};
    
    ReferenceCountedArray<Node> slots;
    slots.add (slot1Node);
    slots.add (slot2Node);
    
    for(int i = 0; i < choices.size(); i++)
    {
        auto& choice = choices.getReference(i);
        auto slot = slots.getUnchecked(i); //https://docs.juce.com/master/classReferenceCountedArray.html#a3d46537444a37fec94bdc623b2ab3211
        
        if (*choice == 0.0f)
        {
            if (slot != nullptr)
            {
                mainProcessor->removeNode (slot);
                slots.set (i, nullptr);
                hasChanged = true;
            }
        }
        else if (*choice == 1.0f)
        {
            if (slot != nullptr)
            {
                if (slot->getProcessor()->getName() == "Highpass")
                    continue;
                mainProcessor->removeNode (slot);
            }
            
            slots.set (i, mainProcessor->addNode(new HighPassFilterProcessor()));
            
            hasChanged = true;
        }
        else if (*choice == 2.0f)
        {
            if (slot != nullptr)
            {
                if (slot->getProcessor()->getName() == "Lowpass")
                    continue;
                mainProcessor->removeNode (slot);
            }
            slots.set (i, mainProcessor->addNode(new LowPassFilterProcessor()));
            hasChanged = true;
        }
        else if (*choice == 3.0f)
        {
            if (slot != nullptr)
            {
                if (slot->getProcessor()->getName() == "Filter")
                    continue;
                mainProcessor->removeNode (slot);
            }
            slots.set (i, mainProcessor->addNode(new FilterProcessor()));
            hasChanged = true;
        }
        
    }

    
    if (hasChanged)
    {
        for (auto connection : mainProcessor->getConnections()) // [5]
            mainProcessor->removeConnection (connection);
        
        ReferenceCountedArray<Node> activeSlots;

        for (auto slot : slots)
        {
            if (slot != nullptr)
            {
                activeSlots.add (slot);
                
                slot->getProcessor()->setPlayConfigDetails (getMainBusNumInputChannels(),
                                                            getMainBusNumOutputChannels(),
                                                            getSampleRate(), getBlockSize());
            }
        }
        
        if (activeSlots.isEmpty())                              // [7]
        {
            connectAudioNodes();
        }
        else
        {
            for (int i = 0; i < activeSlots.size() - 1; ++i)    // [8]
            {
                for (int channel = 0; channel < 2; ++channel)
                    mainProcessor->addConnection (
                                                  {
                                                      {activeSlots.getUnchecked (i)->nodeID, channel},
                                                      {activeSlots.getUnchecked (i + 1)->nodeID, channel}
                                                  });
            }
            
            for (int channel = 0; channel < 2; ++channel)       // [9]
            {


                mainProcessor->addConnection (
                                              {
                                                  { audioInputNode->nodeID, channel },
                                                  { activeSlots.getFirst()->nodeID, channel }
                                              });
                mainProcessor->addConnection (
                                              {
                                                  { activeSlots.getLast()->nodeID, channel },
                                                  { audioInputNode->nodeID, channel }
                                              });
            }
            std::cout << "======================"<< std::endl;
            
            for (auto node : mainProcessor->getNodes()){
                std::cout << node->nodeID << std::endl;
                std::cout << node->getProcessor()->getName() << std::endl;
                std::cout << ""<< std::endl;
            }
            std::cout << "+++++++++++++++++++++++"<< std::endl;
        }
        connectMidiNodes();
        for (auto node : mainProcessor->getNodes()){
            node->getProcessor()->enableAllBuses();
        }
        slot1Node = slots.getUnchecked (0);
        slot2Node = slots.getUnchecked (1);
    }
}


//==============================================================================
bool FilterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* FilterAudioProcessor::createEditor()
{
    return new FilterAudioProcessorEditor (*this);
}

//==============================================================================
void FilterAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FilterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FilterAudioProcessor();
}
