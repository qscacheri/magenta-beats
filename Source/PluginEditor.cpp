/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MagentaBeatsAudioProcessorEditor::MagentaBeatsAudioProcessorEditor (MagentaBeatsAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    test.reset(new TextButton());
    test->setButtonText("Test");
    test->onClick = [&]{ processor.runFunction(); };
    addAndMakeVisible(test.get());
    
    
    setSize (400, 300);
}

MagentaBeatsAudioProcessorEditor::~MagentaBeatsAudioProcessorEditor()
{
}

//==============================================================================
void MagentaBeatsAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void MagentaBeatsAudioProcessorEditor::resized()
{
    test->setBounds(getLocalBounds());
}
