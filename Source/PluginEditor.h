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
class MagentaBeatsAudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener
{
public:
    static int sequencerSelect;
    
    MagentaBeatsAudioProcessorEditor (MagentaBeatsAudioProcessor&);
    ~MagentaBeatsAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void paintLoading(Graphics& g);
    
    // slider listener
    void sliderValueChanged(Slider* s) override;
private:
    std::unique_ptr<SequencerComponent> sequencerComponent1;
    std::unique_ptr<SequencerComponent> sequencerComponent2;
    
    std::unique_ptr<DrawableButton> createMagentaButton;
    std::unique_ptr<DrawableButton> recycleButton;

    std::unique_ptr<Slider> temperatureSlider;
    
    std::unique_ptr<Drawable> snowflake;
    std::unique_ptr<Drawable> flame;

    std::unique_ptr<ShapeButton> userButton;
    std::unique_ptr<ShapeButton> magentaButton;

    std::unique_ptr<DrawableButton> sequencerSelectButton;
    
    Font defaultFont;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MagentaBeatsAudioProcessor& processor;
    std::unique_ptr<TextButton> test;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MagentaBeatsAudioProcessorEditor)
};

