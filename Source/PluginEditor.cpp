/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

int MagentaBeatsAudioProcessorEditor::sequencerSelect = 1;

//==============================================================================
MagentaBeatsAudioProcessorEditor::MagentaBeatsAudioProcessorEditor (MagentaBeatsAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    Colour userColour = Colour(0xff34d8eb);
    Colour magentaColour = Colours::magenta;
    sequencerComponent1.reset(new SequencerComponent(processor.getSequencer(MagentaBeatsAudioProcessor::SequencerType::userSeq)));
    sequencerComponent1->setLookAndFeel(&LookAndFeel::getDefaultLookAndFeel());
    sequencerComponent1->setColour(SequencerComponent::ColourIds::beatColourOffId, Colour(0xff34d8eb));
    addAndMakeVisible(sequencerComponent1.get());
    
    sequencerComponent2.reset(new SequencerComponent(processor.getSequencer(MagentaBeatsAudioProcessor::SequencerType::magentaSeq), true));
    sequencerComponent2->isSelected = false;
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
    recycleButton->onClick = [&] { processor.swapSequences(); };
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

    Path path;
    path.addEllipse(0, 0, 10, 10);
    
    userButton.reset(new ShapeButton("userSelect", userColour.darker(.5f), userColour.darker(.5f), userColour));
    userButton->setOnColours(userColour, userColour, userColour);
    userButton->shouldUseOnColours(true);
    userButton->setShape(path, true, true, true);
    userButton->setRadioGroupId(1);
    userButton->addListener(sequencerComponent1.get());
    userButton->setClickingTogglesState(true);
    userButton->setToggleState(true, NotificationType::dontSendNotification);
    addAndMakeVisible(userButton.get());
    
    magentaButton.reset(new ShapeButton("userSelect", magentaColour.darker(.5f), magentaColour.darker(.5f), magentaColour));
    magentaButton->setOnColours(magentaColour, magentaColour, magentaColour);
    magentaButton->shouldUseOnColours(true);
    magentaButton->setShape(path, true, true, true);
    magentaButton->setRadioGroupId(1);
    magentaButton->addListener(sequencerComponent2.get());
    magentaButton->setClickingTogglesState(true);
    addAndMakeVisible(magentaButton.get());

    std::unique_ptr<Drawable> userImage = Drawable::createFromImageData(BinaryData::user_on_svg, BinaryData::user_on_svgSize);
    std::unique_ptr<Drawable> magentaImage =  Drawable::createFromImageData(BinaryData::magenta_on_svg, BinaryData::magenta_on_svgSize);

    sequencerSelectButton.reset(new DrawableButton("sequencerSelect", DrawableButton::ButtonStyle::ImageFitted));
    sequencerSelectButton->setClickingTogglesState(true);
    sequencerSelectButton->setImages(userImage.get(), nullptr, nullptr, nullptr, magentaImage.get());
    sequencerSelectButton->onStateChange = [&]
    {
        processor.setSelectedSequencer(sequencerSelectButton->getToggleState());
        sequencerComponent1->isSelected = !sequencerSelectButton->getToggleState();
        sequencerComponent2->isSelected = sequencerSelectButton->getToggleState();
    };
    addAndMakeVisible(sequencerSelectButton.get());
    
    setSize (1100, 700);
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
    
    area = area.withSizeKeepingCentre(area.getWidth() * .45, area.getWidth() * .45);
    sequencerSelectButton->setBounds(area);
    
    area = temperatureSlider->getBounds();
    area.translate(area.getWidth(), 0);
    area = area.withSizeKeepingCentre(area.getWidth() * .25, area.getWidth() * .25);
//    sequencerSelectButton->setBounds(area);


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
