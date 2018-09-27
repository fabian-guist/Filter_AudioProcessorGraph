/*
  ==============================================================================

    HighPassFilterProcessor.cpp
    Created: 29 Jul 2018 4:26:07pm
    Author:  Fabian Guist

  ==============================================================================
*/
#include "Oscilator.h"

OscilatorProcessor::OscilatorProcessor() : FilterAudioProcessor()
{
    oscillator.setFrequency (200.0f);
    oscillator.initialise ([] (float x) { return std::sin (x); });
}

void OscilatorProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    dsp::ProcessSpec spec { sampleRate, static_cast<uint32> (samplesPerBlock) };
    oscillator.prepare (spec);
}

void OscilatorProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    dsp::AudioBlock<float> block (buffer);
    dsp::ProcessContextReplacing<float> context (block);
    oscillator.process (context);
}
