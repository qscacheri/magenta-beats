/*
  ==============================================================================

    ArchedSliderLookAndFeel.h
    Created: 20 Nov 2019 1:10:41pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

class ArchedSliderLookAndFeel
{
public:
    static void drawRotarySlider (Graphics &g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &slider)
    {        
        int w = slider.getWidth();
        int h = slider.getHeight();
        Path p;
        
        float outline = w / 6;
        
        p.addArc(0, 0, w, h, (rotaryStartAngle),
                 (rotaryEndAngle), true);
        
        p.applyTransform(AffineTransform::scale(1.f - (outline / w), 1.f - (outline / h), w / 2, h / 2));
        g.setColour(slider.findColour(Slider::ColourIds::backgroundColourId));
        g.strokePath(p, PathStrokeType(outline));
        p.clear();
        
        g.setColour(Colours::white);
        p.addArc(0, 0, w, h, (rotaryStartAngle),
                 (rotaryStartAngle + sliderPosProportional * 4.84), true);
        p.applyTransform(AffineTransform::scale(1.f - (outline / w), 1.f - (outline / h), w / 2, h / 2));
        g.setColour(slider.findColour(Slider::ColourIds::rotarySliderFillColourId));
        g.strokePath(p, PathStrokeType(outline));
    }

};
