#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

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
    
    Label slot1Label;
    Label slot2Label;
    Label slot3Label;
    
    ComboBox slot1Combobox;
    ComboBox slot2Combobox;
    ComboBox slot3Combobox;
    
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> slot1ComboboxAttachment;
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> slot2ComboboxAttachment;
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> slot3ComboboxAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterAudioProcessorEditor)
};
