/*
  ==============================================================================

    LowPassFilterProcessor.h
    Created: 29 Jul 2018 4:26:18pm
    Author:  Fabian Guist

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class LowPassFilterProcessor  : public FilterAudioProcessor
{
public:
    LowPassFilterProcessor();
    const String getName() const override { return "Lowpass"; }
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    void updateFilter();
    
private:
    float lastSampleRate;

    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> lowPassFilter;
};
