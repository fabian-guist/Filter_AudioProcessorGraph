/*
  ==============================================================================

    Filter.h
    Created: 24 Sep 2018 3:50:59pm
    Author:  Fabian Guist

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class FilterProcessor  : public FilterAudioProcessor
{
public:
    FilterProcessor();
    const String getName() const override { return "Filter"; }
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;
    
private:
    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> filter;
};
