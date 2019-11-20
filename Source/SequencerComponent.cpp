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
SequencerComponent::SequencerComponent(Sequencer &s) : sequencer(s)
{
    setColour(ColourIds::backgroundColourId, Colours::black);
    setColour(ColourIds::beatColourOffId, Colours::magenta);
    setColour(ColourIds::beatColourOnId, Colours::magenta);

}

SequencerComponent::~SequencerComponent()
{
}

void SequencerComponent::paint (Graphics& g)
{
    g.fillAll(findColour(ColourIds::backgroundColourId));
    
    int totalLength = sequencer.getTotalLength();
    float xDist = (float)getWidth() / totalLength;
    float yDist = (float)getHeight() / 4;
    
    Rectangle<float> area(0, 0, xDist, yDist);
    
    for (int rows = 0; rows < 4; rows++)
    {
        
        for (int cols = 0; cols < totalLength; cols++)
        {
            g.setColour(findColour(ColourIds::beatColourOffId));
            qtils::drawRoundedRectInside(g, area.withSizeKeepingCentre(xDist * .9, yDist * .9), area.getWidth() / 3, 1.f);
            area.translate(xDist, 0);
        }
        
        area.translate(0, yDist);
        area.setX(0);
    }

}

void SequencerComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

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
        DBG(sequence->toString());
    }
}


std::pair<int, int> SequencerComponent::checkClick(Point<float> p)
{
    int totalLength = sequencer.getTotalLength();
    float xDist = getWidth() / totalLength;
    float yDist = getHeight() / 4;
    
    Rectangle<float> area(0, 0, xDist, yDist);
    
    for (int rows = 0; rows < 3; rows++)
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
                return std::pair<int, int>(rows, cols);
        }
    }
    return std::pair<int, int>(-1, -1);
}

