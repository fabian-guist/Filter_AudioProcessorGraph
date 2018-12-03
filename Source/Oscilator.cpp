#include "Oscilator.h"

OscilatorProcessor::OscilatorProcessor() : FilterAudioProcessor()
{
    oscillator.setFrequency (200.0f);
    oscillator.initialise ([] (float x) { return std::sin (x); });
}

void OscilatorProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    
    oscillator.prepare (spec);
}

void OscilatorProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    for (auto i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    dsp::AudioBlock<float> block (buffer);
    dsp::ProcessContextReplacing<float> context (block);
    oscillator.process (context);
}
