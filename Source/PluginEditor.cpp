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
    test->onClick = [&]{
        processor.runFunction(); };
    addAndMakeVisible(test.get());
    
    std::unique_ptr<Drawable> image = Drawable::createFromImageData(BinaryData::down_arrow_png, BinaryData::down_arrow_pngSize);
    
    createMagentaButton.reset(new DrawableButton("create", DrawableButton::ButtonStyle::ImageFitted));
    createMagentaButton->setImages(image.get());
    createMagentaButton->onClick = [&]{
        if (!processor.areModulesLoaded())
        {
            AlertWindow::showMessageBox(AlertWindow::AlertIconType::InfoIcon, "Loading necessary data", "Magenta Beats is loading the necessary data to create new beats. This only happens the first time a new beat is created");
        }
        processor.applyModel();
        
        
    };
    addAndMakeVisible(createMagentaButton.get());
    
    image.reset();
    image = Drawable::createFromImageData(BinaryData::up_arrow_png, BinaryData::up_arrow_pngSize);
    
    recycleButton.reset(new DrawableButton("create", DrawableButton::ButtonStyle::ImageFitted));
    recycleButton->setImages(image.get());
    addAndMakeVisible(recycleButton.get());

    temperatureSlider.reset(new Slider());
    temperatureSlider->setSliderStyle(Slider::SliderStyle::Rotary);
    temperatureSlider->setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::magenta);
    temperatureSlider->setColour(Slider::ColourIds::backgroundColourId, Colour(0xff34d8eb));
    temperatureSlider->setRange(0, 100.0);
    temperatureSlider->setTextValueSuffix("%");
    addAndMakeVisible(temperatureSlider.get());
    
    snowflake = Drawable::createFromImageData(BinaryData::snow_flake_svg, BinaryData::snow_flake_svgSize);
    
    flame = Drawable::createFromImageData(BinaryData::flame_svg, BinaryData::flame_svgSize);
    
    defaultFont = Font(Typeface::createSystemTypefaceFor(BinaryData::JosefinSansLight_ttf, BinaryData::JosefinSansLight_ttfSize));

    setSize (1200, 800);
}

MagentaBeatsAudioProcessorEditor::~MagentaBeatsAudioProcessorEditor()
{
    
}

//==============================================================================
void MagentaBeatsAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    if (!processor.areModulesLoaded())
        paintLoading(g);
    
    g.setColour (Colours::white);
    g.setFont (15.0f);
    
    g.fillAll(Colours::black);
    
    Rectangle<float> area(200, 200, getHeight() / 20, getHeight() / 20);
    area.setX(temperatureSlider->getBounds().getX() - area.getWidth());
    area.setY(temperatureSlider->getBounds().getBottom() - area.getHeight());
    
    snowflake->drawWithin(g, area, RectanglePlacement::fillDestination, 1.f);
    
    area.setX(temperatureSlider->getBounds().getRight());
    flame->drawWithin(g, area, RectanglePlacement::fillDestination, 1.f);
    
    Font f = defaultFont;
    f.setHeight(getHeight() * .08);
    g.setFont(f);
    g.drawFittedText("-Magenta Beats-", 0, 0, getWidth(), getHeight() * .1, Justification::left, 1);
    
    g.setColour(Colours::lightgrey.darker(.5));
    f.setHeight(getHeight() * .05);
    g.setFont(f);
    g.drawFittedText("Quin Scacheri", getWidth() - getWidth() * .25, getHeight() - getHeight() * .05, getWidth() * .25, getHeight() * .05, Justification::right, 1);

}

void MagentaBeatsAudioProcessorEditor::resized()
{
    Rectangle<int> controlArea = getLocalBounds();
    controlArea.removeFromBottom(getHeight() * .1);
    controlArea.removeFromTop(getHeight() * .1);

    Rectangle<int> area = controlArea;
    area = area.removeFromTop(controlArea.getHeight() / 4);
    sequencerComponent1->setBounds(area);
    
    area = area.withY(controlArea.getBottom() - area.getHeight());
    sequencerComponent2->setBounds(area);
    
    area = controlArea;
    area.removeFromTop(controlArea.getHeight() / 4);
    area.removeFromBottom(controlArea.getHeight() / 4);
    area = area.removeFromLeft(controlArea.getWidth() / 4);
    createMagentaButton->setBounds(area.withSizeKeepingCentre(area.getWidth() * .75, area.getHeight() * .75));
    
    area.setX(controlArea.getWidth() - area.getWidth());
    recycleButton->setBounds(area.withSizeKeepingCentre(area.getWidth() * .75, area.getHeight() * .75));
    
    area.setX(controlArea.getWidth() / 2 - area.getWidth() / 2);
    area = area.withSizeKeepingCentre(area.getWidth(), area.getWidth());
    temperatureSlider->setBounds(area);
    
}

void MagentaBeatsAudioProcessorEditor::paintLoading(Graphics& g)
{
    g.setColour(Colours::white);
    g.drawFittedText("Loading awesomeness...", getLocalBounds(), Justification::centred, 1);
}

void MagentaBeatsAudioProcessorEditor::sliderValueChanged(Slider* s)
{
    processor.temperatureParam = s->getValue();
}
