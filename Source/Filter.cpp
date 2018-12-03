#include "Filter.h"

FilterProcessor::FilterProcessor() : FilterAudioProcessor()
{
  
}

void FilterProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    *highpassFilter.state = *dsp::IIR::Coefficients<float>::makeHighPass (sampleRate, 1000.0f);
    dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumInputChannels();
    
    highpassFilter.prepare (spec);
    highpassFilter.reset();
}

void FilterProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    for (auto i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    dsp::AudioBlock<float> block (buffer);
    dsp::ProcessContextReplacing<float> context (block);
    highpassFilter.process (context);
}

