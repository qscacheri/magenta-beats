/*
  ==============================================================================

    Sequencer.h
    Created: 8 Nov 2019 1:53:40am
    Author:  Quin Scacheri

  ==============================================================================
*/

#pragma once
#include "NoteSequence.h"
#include "JuceHeader.h"

class Sequencer
{
public:
    Sequencer();
    
    int getTotalLength() { return totalLength; }
    
    NoteSequence* getNoteSequence() { return &sequence; };
    
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    
    void processBlock(MidiBuffer &midiBuffer);
    
private:
    NoteSequence sequence;
    int totalLength = 16;
    
    Synthesiser sampler;
    
    
};
