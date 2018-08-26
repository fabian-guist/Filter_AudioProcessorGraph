/*
  ==============================================================================

    HighPassFilterProcessor.cpp
    Created: 29 Jul 2018 4:26:07pm
    Author:  Fabian Guist

  ==============================================================================
*/
#include "HighPassFilterProcessor.h"

HighPassFilterProcessor::HighPassFilterProcessor() : FilterAudioProcessor()
,highPassFilter(dsp::IIR::Coefficients<float>::makeHighPass(44100, 20000, 0.1f))
{
}

void HighPassFilterProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    lastSampleRate = sampleRate;
    
    FilterAudioProcessor filterAudioProcessor;
    dsp::ProcessSpec specLp = filterAudioProcessor.setUpSpec(sampleRate, samplesPerBlock);
    highPassFilter.prepare(specLp);
    highPassFilter.reset();
}

void HighPassFilterProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    for (auto i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    //Juce_DSP Module adden in Projucer
    updateFilter();
    dsp::AudioBlock<float> block (buffer);
    highPassFilter.process(dsp::ProcessContextReplacing<float> (block));
}

void HighPassFilterProcessor::updateFilter()
{
    /*float freqHp = *tree.getRawParameterValue("cutoffLp");
    float resHp = *tree.getRawParameterValue("resonanceLp");
    */
    highPassFilter.state = dsp::IIR::Coefficients<float>::makeHighPass(44100, 20000, 0.1f);
}
