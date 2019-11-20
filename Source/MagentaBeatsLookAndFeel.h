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
    virtual void drawRotarySlider (Graphics &g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &slider) override;

};
