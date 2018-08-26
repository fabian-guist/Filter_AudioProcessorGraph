/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FilterAudioProcessorEditor::FilterAudioProcessorEditor (FilterAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (200, 320);
    
    slot1CutoffSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    slot1CutoffSlider.setRange(0.1f, 500.0f);
    slot1CutoffSlider.setValue(0.1f);
    slot1CutoffSlider.addListener(this);
    slot1CutoffSlider.setTextBoxStyle(Slider::NoTextBox, false, 50, 20);
    addAndMakeVisible(&slot1CutoffSlider);
    
    slot1CutoffSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "slot1Cutoff", slot1CutoffSlider);

    slot2CutoffSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    slot2CutoffSlider.setRange(0.1f, 500.0f);
    slot2CutoffSlider.setValue(0.1f);
    slot2CutoffSlider.addListener(this);
    slot2CutoffSlider.setTextBoxStyle(Slider::NoTextBox, false, 50, 20);
    addAndMakeVisible(&slot2CutoffSlider);
    
    slot2CutoffSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "slot2Cutoff", slot1CutoffSlider);

    
    cutoffGroup = new GroupComponent("Cutoff", "Cutoff");
    addAndMakeVisible(cutoffGroup);
    
    slot1ResonanceSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    slot1ResonanceSlider.setRange(0.1f, 500.0f);
    slot1ResonanceSlider.setValue(0.1f);
    slot1ResonanceSlider.addListener(this);
    slot1ResonanceSlider.setTextBoxStyle(Slider::NoTextBox, false, 50, 20);
    addAndMakeVisible(&slot1ResonanceSlider);
    
    slot1ResonanceSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "slot1Resonance", slot1ResonanceSlider);
    
    slot2ResonanceSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    slot2ResonanceSlider.setRange(0.1f, 500.0f);
    slot2ResonanceSlider.setValue(0.1f);
    slot2ResonanceSlider.addListener(this);
    slot2ResonanceSlider.setTextBoxStyle(Slider::NoTextBox, false, 50, 20);
    addAndMakeVisible(&slot2ResonanceSlider);
    
    slot2ResonanceSliderAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "slot2Resonance", slot2ResonanceSlider);
    
    slot1Bypass.setButtonText ("Bypass");
    slot1Bypass.setToggleState (false, dontSendNotification);
    addAndMakeVisible (slot1Bypass);
    
    slot1BypassAttachment = new AudioProcessorValueTreeState::ButtonAttachment(processor.tree, "slot1Mute", slot1Bypass);

    slot2Bypass.setButtonText ("Bypass");
    slot2Bypass.setToggleState (false, dontSendNotification);
    addAndMakeVisible (slot2Bypass);
    
    slot2BypassAttachment= new AudioProcessorValueTreeState::ButtonAttachment(processor.tree, "slot2Mute",  slot2Bypass);
    
    slot1Combobox.addItem ("Empty", 1);
    slot1Combobox.addItem ("Highpass", 2);
    slot1Combobox.addItem ("Lowpass", 3);
    slot1Combobox.addItem ("Filter", 4);
    slot1Combobox.setSelectedId (1);
    slot1Combobox.setColour (ComboBox::outlineColourId, Colours::transparentBlack);
    addAndMakeVisible (slot1Combobox);
    
    slot1ComboboxAttachment = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "processorSlot1", slot1Combobox);
    
    slot2Combobox.addItem ("Empty", 1);
    slot2Combobox.addItem ("Highpass", 2);
    slot2Combobox.addItem ("Lowpass", 3);
    slot2Combobox.setSelectedId (1);
    slot2Combobox.setColour (ComboBox::outlineColourId, Colours::transparentBlack);
    addAndMakeVisible (slot2Combobox);
    
    slot2ComboboxAttachment = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "processorSlot2", slot2Combobox);
    
    resonanceGroup = new GroupComponent("Resonance", "Resonance");
    addAndMakeVisible(resonanceGroup);
}

FilterAudioProcessorEditor::~FilterAudioProcessorEditor()
{
}

void FilterAudioProcessorEditor::sliderValueChanged(Slider* slider)
{

}

//==============================================================================
void FilterAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void FilterAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    slot1CutoffSlider.setBounds(0, 60, 100, 100);
    slot1ResonanceSlider.setBounds(100, 60, 100, 100);
    
    slot2CutoffSlider.setBounds(0, 220, 100, 100);
    slot2ResonanceSlider.setBounds(100, 220, 100, 100);
    
    slot1Bypass.setBounds(10, 10, 100, 20);
    slot2Bypass.setBounds(10, 170, 100, 20);
    
    slot1Combobox.setBounds(10, 40, 100, 20);
    slot2Combobox.setBounds(10, 200, 100, 20);

    
    
}
