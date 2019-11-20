/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "SequencerComponent.h"
//==============================================================================
/**
*/
class MagentaBeatsAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    MagentaBeatsAudioProcessorEditor (MagentaBeatsAudioProcessor&);
    ~MagentaBeatsAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void paintLoading(Graphics& g);
private:
    std::unique_ptr<SequencerComponent> sequencerComponent1;
    std::unique_ptr<SequencerComponent> sequencerComponent2;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MagentaBeatsAudioProcessor& processor;
    std::unique_ptr<TextButton> test;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MagentaBeatsAudioProcessorEditor)
};

