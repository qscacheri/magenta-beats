/*
  ==============================================================================

    MagentaBeatsLookAndFeel.cpp
    Created: 20 Nov 2019 1:10:20pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#include "MagentaBeatsLookAndFeel.h"

void MagentaBeatsLookAndFeel::drawRotarySlider (Graphics &g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &slider)
{
    ArchedSliderLookAndFeel::drawRotarySlider(g, x, y, width, height, sliderPosProportional, rotaryStartAngle, rotaryEndAngle, slider);
}
