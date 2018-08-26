/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class FilterAudioProcessorEditor  : public AudioProcessorEditor,
public Slider::Listener
{
public:
    FilterAudioProcessorEditor (FilterAudioProcessor&);
    ~FilterAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider* slider) override;
    void updateAssignSelf();


private:
    
    AudioParameterFloat* getParameterForSlider (Slider* slider);
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FilterAudioProcessor& processor;
    
    Slider slot1CutoffSlider;
    Slider slot1ResonanceSlider;
    
    Slider slot2CutoffSlider;
    Slider slot2ResonanceSlider;
    
    ToggleButton slot1Bypass;
    ToggleButton slot2Bypass;
    
    Label cutoffLabel;
    Label resonanceLabel;
    
    ComboBox slot1Combobox;
    ComboBox slot2Combobox;
    
    GroupComponent* cutoffGroup;
    GroupComponent* resonanceGroup;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> slot1CutoffSliderAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> slot2CutoffSliderAttachment;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> slot1ResonanceSliderAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> slot2ResonanceSliderAttachment;
    
    ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> slot1BypassAttachment;
    ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> slot2BypassAttachment;

    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> slot1ComboboxAttachment;
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> slot2ComboboxAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterAudioProcessorEditor)
};
