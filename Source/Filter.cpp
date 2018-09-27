/*
  ==============================================================================

    Filter.cpp
    Created: 24 Sep 2018 3:50:59pm
    Author:  Fabian Guist

  ==============================================================================
*/

#include "Filter.h"

FilterProcessor::FilterProcessor() : FilterAudioProcessor()
{
  
}

void FilterProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    *filter.state = *dsp::IIR::Coefficients<float>::makeHighPass (sampleRate, 1000.0f);
    dsp::ProcessSpec spec { sampleRate, static_cast<uint32> (samplesPerBlock), 2 };
    filter.prepare (spec);
}

void FilterProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    dsp::AudioBlock<float> block (buffer);
    dsp::ProcessContextReplacing<float> context (block);
    filter.process (context);
}

