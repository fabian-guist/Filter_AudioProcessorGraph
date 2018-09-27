/*
  ==============================================================================

    HighPassFilterProcessor.h
    Created: 29 Jul 2018 4:26:07pm
    Author:  Fabian Guist

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class OscilatorProcessor  : public FilterAudioProcessor
{
public:
    OscilatorProcessor();
    const String getName() const override { return "Oscilator"; }
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;
    
private:
    dsp::Oscillator<float> oscillator;
};
