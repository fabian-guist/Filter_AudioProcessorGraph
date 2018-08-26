/*
  ==============================================================================

    LowPassFilterProcessor.cpp
    Created: 29 Jul 2018 4:26:18pm
    Author:  Fabian Guist

  ==============================================================================
*/

#include "LowPassFilterProcessor.h"

LowPassFilterProcessor::LowPassFilterProcessor() : FilterAudioProcessor()
,lowPassFilter(dsp::IIR::Coefficients<float>::makeLowPass(44100, 20000, 0.1f))
{
}

void LowPassFilterProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    lastSampleRate = sampleRate;

    FilterAudioProcessor filterAudioProcessor;
    dsp::ProcessSpec specLp = filterAudioProcessor.setUpSpec(sampleRate, samplesPerBlock);
    lowPassFilter.prepare(specLp);
    lowPassFilter.reset();
}

void LowPassFilterProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    for (auto i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    //Juce_DSP Module adden in Projucer
    updateFilter();
    dsp::AudioBlock<float> block (buffer);
    lowPassFilter.process(dsp::ProcessContextReplacing<float> (block));
}

void LowPassFilterProcessor::updateFilter()
{
    /*float freqLp = *tree.getRawParameterValue("cutoffLp");
    float resLp = *tree.getRawParameterValue("resonanceLp");*/
    
    lowPassFilter.state = dsp::IIR::Coefficients<float>::makeLowPass(44100, 20000, 0.1f);
}
