/*
  ==============================================================================

    SequencerComponent.cpp
    Created: 8 Nov 2019 1:53:21am
    Author:  Quin Scacheri

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SequencerComponent.h"
#include "qtils.h"

//==============================================================================
SequencerComponent::SequencerComponent(Sequencer &s, bool shouldFlip) : sequencer(s)
{
    
    this->shouldFlip = shouldFlip;
    
    setColour(ColourIds::backgroundColourId, Colours::black);
    setColour(ColourIds::beatColourOffId, Colours::magenta);
    setColour(ColourIds::beatColourOnId, Colours::magenta);

    lengthSlider.reset(new Slider());
    lengthSlider->setSliderStyle(Slider::SliderStyle::Rotary);
    lengthSlider->setColour(Slider::ColourIds::rotarySliderFillColourId, findColour(ColourIds::beatColourOffId));
    lengthSlider->setColour(Slider::ColourIds::backgroundColourId, Colours::white);
}

SequencerComponent::~SequencerComponent()
{
}

void SequencerComponent::paint (Graphics& g)
{
    g.fillAll(findColour(ColourIds::backgroundColourId));
    paintGrid(g);
}

void SequencerComponent::paintGrid(Graphics& g)
{
    NoteSequence* sequence = sequencer.getNoteSequence();
    int totalLength = sequencer.getTotalLength();
    float xDist = (float)getWidth() / totalLength;
    float yDist = (float)getHeight() / 4;
    
    Rectangle<float> area(0, 0, xDist, yDist);
    
    for (int rows = 0; rows < 4; rows++)
    {
        
        for (int cols = 0; cols < totalLength; cols++)
        {
            g.setColour(findColour(ColourIds::beatColourOffId));
            if (sequence->isNotePresent(NoteSequence::noteValues[rows], cols))
            {
               g.fillRoundedRectangle(area.withSizeKeepingCentre(xDist * .9, yDist * .9), area.getWidth() / 3);
            }
            qtils::drawRoundedRectInside(g, area.withSizeKeepingCentre(xDist * .9, yDist * .9), area.getWidth() / 3, 1.f);
            area.translate(xDist, 0);
        }
        
        area.translate(0, yDist);
        area.setX(0);
    }
    Rectangle<float> selectedRowArea(0, 0, getWidth(), getHeight() / 8);
    
    selectedRowArea.translate(0, yDist * selectedRow);
    g.setColour(Colours::white.withAlpha(.4f));


}

void SequencerComponent::resized()
{
    auto area = getLocalBounds();
    if (shouldFlip)
        area.removeFromBottom(getHeight() / 2);
    else
        area.removeFromTop(getHeight() / 2);
    
    area = area.withSizeKeepingCentre(area.getHeight(), area.getHeight());
//    lengthSlider->setBounds(area);
}


void SequencerComponent::mouseUp(const MouseEvent& e)
{
    Component::mouseUp(e);
    std::pair<int, int> result = checkClick(e.getMouseDownPosition().toFloat());

    if (result.first !=-1)
    {
        
        int pitch = NoteSequence::noteValues[result.first];
        int startTime = result.second;

        NoteSequence* sequence = sequencer.getNoteSequence();
        if (sequence->checkAndRemoveNote(pitch, startTime))
            DBG("removed");
        else
        {
            sequence->addNote(Note(pitch, 100, startTime, startTime + 1));
        }
    }
    
    repaint();
}


std::pair<int, int> SequencerComponent::checkClick(Point<float> p)
{
    int totalLength = sequencer.getTotalLength();
    float xDist = getWidth() / totalLength;
    float yDist = getHeight() / 4;
    
    Rectangle<float> area(0, 0, xDist, yDist);

    for (int rows = 0; rows < 4; rows++)
    {
        if (p.getY() > area.getBottom())
        {
            area.translate(0, yDist);
            continue;
        }
        for (int cols = 0; cols < totalLength; cols++){

            if (p.getX() > area.getRight())
            {
                area.translate(xDist, 0);
                continue;
            }

            if (area.contains(p))
            {
                selectedRow = rows;
                return std::pair<int, int>(rows, cols);
            }
        }
    }
    return std::pair<int, int>(-1, -1);
    
}

void SequencerComponent::colourChanged()
{
    if (isColourSpecified(ColourIds::beatColourOffId && lengthSlider != nullptr))
        lengthSlider->setColour(Slider::ColourIds::rotarySliderFillColourId, findColour(ColourIds::beatColourOffId));
}

