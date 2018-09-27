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
    setSize (150, 180);

    slot1Label.setText("Slot1", dontSendNotification);
    addAndMakeVisible(slot1Label);
    
    slot1Combobox.addItem ("Empty", 1);
    slot1Combobox.addItem ("Oscilator", 2);
    slot1Combobox.addItem ("Gain", 3);
    slot1Combobox.addItem ("Filter", 4);
    slot1Combobox.setSelectedId (1);
    slot1Combobox.setColour (ComboBox::outlineColourId, Colours::transparentBlack);
    addAndMakeVisible (slot1Combobox);
    
    slot1ComboboxAttachment = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "processorSlot1", slot1Combobox);
    
    slot2Label.setText("Slot2", dontSendNotification);
    addAndMakeVisible(slot2Label);

    slot2Combobox.addItem ("Empty", 1);
    slot2Combobox.addItem ("Oscilator", 2);
    slot2Combobox.addItem ("Gain", 3);
    slot2Combobox.addItem ("Filter", 4);
    slot2Combobox.setSelectedId (1);
    slot2Combobox.setColour (ComboBox::outlineColourId, Colours::transparentBlack);
    addAndMakeVisible (slot2Combobox);
    slot2ComboboxAttachment = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "processorSlot2", slot2Combobox);
    
    slot3Label.setText("Slot3", dontSendNotification);
    addAndMakeVisible(slot3Label);

    slot3Combobox.addItem ("Empty", 1);
    slot3Combobox.addItem ("Oscilator", 2);
    slot3Combobox.addItem ("Gain", 3);
    slot3Combobox.addItem ("Filter", 4);
    slot3Combobox.setSelectedId (1);
    slot3Combobox.setColour (ComboBox::outlineColourId, Colours::transparentBlack);
    addAndMakeVisible (slot3Combobox);
    
    slot3ComboboxAttachment = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree, "processorSlot3", slot3Combobox);
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
    
    slot1Label.setBounds(10, 0, 100, 20);
    slot1Combobox.setBounds(10, 30, 100, 20);
    
    slot2Label.setBounds(10, 60, 100, 20);
    slot2Combobox.setBounds(10, 90, 100, 20);
    
    slot3Label.setBounds(10, 120, 100, 20);
    slot3Combobox.setBounds(10, 150, 100, 20);
}
