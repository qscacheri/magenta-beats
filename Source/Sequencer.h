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
#include <array>

class Sequencer
{
public:
    
    enum DrumMidiNote: int
    {
        kickMidiNote = 36,
        snareMidiNote = 38,
        hhCLosedMidiNote = 42,
        hhOpenMidiNote = 46
    };

    Sequencer();
    
    int getTotalLength() { return totalLength; }
    
    NoteSequence* getNoteSequence() { return &sequence; };
    
    void prepareToPlay(double sampleRate);
    
    void processBlock(AudioPlayHead* p, AudioBuffer<float> &buffer, MidiBuffer &midiBuffer);
    void addToBufferIfNeeded(int which, int samplesPerBlock, MidiBuffer &midiBuffer);
    
    ValueTree getStateInformation();
    void setStateInformation(ValueTree tree);
    
private:
    
    NoteSequence sequence;
    AudioPlayHead* playhead;
    Synthesiser sampler;
    AudioFormatManager formatManager;
    float lastSampleRate = 48000;
    int totalLength = 16;
    std::array<SynthesiserSound::Ptr, 4> samplerSounds;    
};
