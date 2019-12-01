/*
  ==============================================================================

    Sequencer.cpp
    Created: 8 Nov 2019 1:53:40am
    Author:  Quin Scacheri

  ==============================================================================
*/

#include "Sequencer.h"

Sequencer::Sequencer()
{
    sequence.reset(new NoteSequence());
    
    formatManager.registerBasicFormats();
    sampler.clearVoices();
    for (int i = 0; i < 4; i++){
        sampler.addVoice(new SamplerVoice());
    }
    std::unique_ptr<AudioFormatReader> reader;
    
    BigInteger range;
    range.setBit(DrumMidiNote::kickMidiNote);
    reader.reset(formatManager.createReaderFor (new MemoryInputStream(BinaryData::kick_wav, BinaryData::kick_wavSize, false)));
    samplerSounds[0] = new SamplerSound("kick", *reader.get(), range, DrumMidiNote::kickMidiNote, 0, 10, 10.0);
    
    range.clear();
    range.setBit(DrumMidiNote::snareMidiNote);
    reader.reset(formatManager.createReaderFor (new MemoryInputStream(BinaryData::snare_wav, BinaryData::snare_wavSize, false)));
    samplerSounds[1] = new SamplerSound("snare", *reader.get(), range, DrumMidiNote::snareMidiNote, 0, 10, 10.0);
    
    range.clear();
    range.setBit(DrumMidiNote::hhCLosedMidiNote);
    reader.reset(formatManager.createReaderFor (new MemoryInputStream(BinaryData::closed_wav, BinaryData::closed_wavSize, false)));
    samplerSounds[2] = new SamplerSound("hat", *reader.get(), range, DrumMidiNote::hhCLosedMidiNote, 0, 10, 10.0);
    
    range.clear();
    range.setBit(DrumMidiNote::hhOpenMidiNote);
    reader.reset(formatManager.createReaderFor (new MemoryInputStream(BinaryData::open_wav, BinaryData::open_wavSize, false)));
    samplerSounds[3] = new SamplerSound("hato", *reader.get(), range, DrumMidiNote::hhOpenMidiNote, 0, 10, 10.0);


    sampler.addSound(samplerSounds[0]);
    sampler.addSound(samplerSounds[1]);
    sampler.addSound(samplerSounds[2]);
    sampler.addSound(samplerSounds[3]);
    range.clear();
}

void Sequencer::prepareToPlay(double sampleRate)
{
    lastSampleRate = sampleRate;
    sampler.setCurrentPlaybackSampleRate(sampleRate);
}

void Sequencer::processBlock(AudioPlayHead* p, AudioBuffer<float> &buffer, MidiBuffer &midiBuffer)
{
    playhead = p;
    
    int numSamples = buffer.getNumSamples();
    if (playhead == nullptr)
        return;
    

    addToBufferIfNeeded(0, numSamples, midiBuffer);
    
    sampler.renderNextBlock(buffer, midiBuffer, 0, buffer.getNumSamples());
}
            
void Sequencer::addToBufferIfNeeded(int which, int samplesPerBlock, MidiBuffer &midiBuffer)
{
    // get current position
    AudioPlayHead::CurrentPositionInfo currentPos;
    playhead->getCurrentPosition(currentPos);
    if (!currentPos.isPlaying)
        return;
    long long posInSamples = currentPos.timeInSamples;
    posInSamples %= NoteSequence::ppqToSamples(16, 120, lastSampleRate);
    auto notes = sequence->getNotes();
    
    int loopEnd = NoteSequence::ppqToSamples(16, sequence->getTempo(), lastSampleRate);
    
    // iterate through all notes
    for (int i = 0; i < notes.size(); i++){
        int beatInSamples = NoteSequence::ppqToSamples(notes[i].startTime, sequence->getTempo(), lastSampleRate);
        
        // check first beat
        if (posInSamples + samplesPerBlock >= loopEnd && posInSamples <= loopEnd && notes[i].startTime == 0)
        {
            DBG("beat 1");
            long long offset = loopEnd - posInSamples;
            midiBuffer.addEvent(MidiMessage::noteOn(1, notes[i].pitch, .8f), offset);
        }
        
        // check all other beats
        else if (beatInSamples > posInSamples &&
            beatInSamples < posInSamples + samplesPerBlock)
        {
//            DBG("beat");
            long long offset = beatInSamples - posInSamples;
            midiBuffer.addEvent(MidiMessage::noteOn(1, notes[i].pitch, .8f), offset);
        }
    }
}

ValueTree Sequencer::getStateInformation()
{
    return sequence->toValueTree();
}

void Sequencer::setStateInformation(ValueTree tree)
{
    sequence->fromValueTree(tree);
}

void Sequencer::setNewSequence(NoteSequence* newSequence)
{
    sequence.reset(newSequence);
    for (int i = 0; i < listeners.size(); i++)
    {
        MessageManager::callAsync([&]{ listeners[i]->sequenceChanged(); });
        
    }
}

void Sequencer::addListener(SequencerListener* l)
{
    listeners.push_back(l);
}

void Sequencer::removeListener(SequencerListener* l)
{
    for (int i = 0; i < listeners.size(); i++)
    {
        if (listeners[i] == l)
            listeners.erase(listeners.begin()+i);
    }
}
