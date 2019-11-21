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
    sequencerComponent1.reset(new SequencerComponent(processor.getSequencer(MagentaBeatsAudioProcessor::SequencerType::userSeq)));
    sequencerComponent1->setLookAndFeel(&LookAndFeel::getDefaultLookAndFeel());
    sequencerComponent1->setColour(SequencerComponent::ColourIds::beatColourOffId, Colour(0xff34d8eb));
    addAndMakeVisible(sequencerComponent1.get());
    
    sequencerComponent2.reset(new SequencerComponent(processor.getSequencer(MagentaBeatsAudioProcessor::SequencerType::magentaSeq), true));
    addAndMakeVisible(sequencerComponent2.get());

    test.reset(new TextButton());
    test->setButtonText("Test");
    test->onClick = [&]{ processor.runFunction(); };
    addAndMakeVisible(test.get());
    
    
    setSize (900, 600);
}

MagentaBeatsAudioProcessorEditor::~MagentaBeatsAudioProcessorEditor()
{
}

//==============================================================================
void MagentaBeatsAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    if (!processor.modulesLoaded())
        paintLoading(g);
    
    g.setColour (Colours::white);
    g.setFont (15.0f);
}

void MagentaBeatsAudioProcessorEditor::resized()
{
    Rectangle<int> area = getLocalBounds();
    area = area.removeFromTop(getHeight() / 2);
//    area.removeFromLeft(getWidth() / 12);
    sequencerComponent1->setBounds(area);
    
    area = area.withY(getHeight() - area.getHeight());
    sequencerComponent2->setBounds(area);
}

void MagentaBeatsAudioProcessorEditor::paintLoading(Graphics& g)
{
    g.setColour(Colours::white);
    g.drawFittedText("Loading awesomeness...", getLocalBounds(), Justification::centred, 1);
}
