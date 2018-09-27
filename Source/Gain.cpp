/*
  ==============================================================================

    LowPassFilterProcessor.cpp
    Created: 29 Jul 2018 4:26:18pm
    Author:  Fabian Guist

  ==============================================================================
*/

#include "Gain.h"

GainProcessor::GainProcessor() : FilterAudioProcessor()
{
    gain.setGainDecibels (+6.0f);
}

void GainProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    dsp::ProcessSpec spec { sampleRate, static_cast<uint32> (samplesPerBlock), 2 };
    gain.prepare (spec);
}

void GainProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    dsp::AudioBlock<float> block (buffer);
    dsp::ProcessContextReplacing<float> context (block);
    gain.process (context);
}
