/*
  ==============================================================================

    SequencerComponent.h
    Created: 8 Nov 2019 1:53:21am
    Author:  Quin Scacheri

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Sequencer.h"
#include <pybind11/pybind11.h>

//==============================================================================
/*
*/
class SequencerComponent : public Component
{
public:
    
    enum ColourIds : int
    {
        backgroundColourId = 1,
        dividerColourId,
        beatColourOffId,
        beatColourOnId,
        playheadColourId
    };
    
    
    SequencerComponent(Sequencer &s);
    ~SequencerComponent();

    
    void paint (Graphics&) override;
    void resized() override;
    
    void mouseUp(const MouseEvent& e) override;
    
    std::pair<int, int> checkClick(Point<float> p);

private:
    Sequencer &sequencer;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SequencerComponent)
};
