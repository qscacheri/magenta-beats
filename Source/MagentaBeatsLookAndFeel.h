/*
  ==============================================================================

    MagentaBeatsLookAndFeel.h
    Created: 20 Nov 2019 1:10:20pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "ArchedSliderLookAndFeel.h"

class  MagentaBeatsLookAndFeel : public LookAndFeel_V4
{
public:
    
    MagentaBeatsLookAndFeel();
    
    virtual void drawRotarySlider (Graphics &g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &slider) override;

    virtual juce::Slider::SliderLayout getSliderLayout (Slider &) override;
    
    virtual Label* createSliderTextBox (Slider &s) override
    {
        Label* l = new Label();
        l->setColour(Label::ColourIds::outlineColourId, Colours::transparentBlack);
        l->setJustificationType(Justification::centred);
        l->setInterceptsMouseClicks(false, false);

        return l;
    }
    
//    virtual void drawAlertBox (Graphics &, AlertWindow &, const Rectangle< int > &textArea, TextLayout &);
};
