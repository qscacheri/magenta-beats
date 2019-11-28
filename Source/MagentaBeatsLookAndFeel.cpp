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

juce::Slider::SliderLayout MagentaBeatsLookAndFeel::getSliderLayout (Slider &slider)
{
    Slider::SliderLayout layout;
    Rectangle<int> bounds = slider.getLocalBounds();

    layout.sliderBounds = bounds;
    bounds = bounds.withSizeKeepingCentre(slider.getWidth() * .5, slider.getHeight() * .5);
    layout.textBoxBounds = bounds;
    
    return layout;
}

