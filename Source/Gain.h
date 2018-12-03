#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class GainProcessor  : public FilterAudioProcessor
{
public:
    GainProcessor();
    const String getName() const override { return "Gain"; }
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;
    
private:
    dsp::Gain<float> gain;
};
