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
    
    class Listener
    {
    public:
        virtual void sequenceChanged()=0;
    };
    
    enum DrumMidiNote: int
    {
        kickMidiNote = 36,
        snareMidiNote = 38,
        clapMidiNote = 39,
        hhCLosedMidiNote = 42,
        hhOpenMidiNote = 46,
        crashMidiNote = 49
    };

    Sequencer();
    
    int getTotalLength() { return totalLength; }
    
    NoteSequence* getNoteSequence() { return sequence.get(); };
    void setNewSequence(NoteSequence* newSequence);
    
    void prepareToPlay(double sampleRate);
    
    void processBlock(AudioPlayHead* p, AudioBuffer<float> &buffer, MidiBuffer &midiBuffer);
    void addToBufferIfNeeded(int which, int samplesPerBlock, MidiBuffer &midiBuffer);
    
    ValueTree getStateInformation();
    void setStateInformation(ValueTree tree);
    
    // listener methods
    void addListener(Listener*);
    void removeListener(Listener*);
    
    void swapSequences(Sequencer &otherSequencer, bool clearOther = true);
    void clearSequence();
    std::unique_ptr<NoteSequence>& getSequenceForSwap();
    
private:
    std::vector<Listener*> listeners;
    
    std::unique_ptr<NoteSequence> sequence;
    AudioPlayHead* playhead;
    Synthesiser sampler;
    AudioFormatManager formatManager;
    float lastSampleRate = 48000;
    int totalLength = 16;
    std::array<SynthesiserSound::Ptr, 6> samplerSounds;    
};
