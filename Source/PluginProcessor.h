/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <Python.h>
#include "NoteSequence.h"
#include "ImportThread.h"
#include <pybind11/stl.h>
#include "Sequencer.h"
#include "LookAndFeelHolder.h"
#include "MagentaBeatsLookAndFeel.h"


//==============================================================================
/**
*/
namespace py = pybind11;
using namespace pybind11::literals; // to bring in the `_a` literal

class MagentaBeatsAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    MagentaBeatsAudioProcessor();
    ~MagentaBeatsAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void runFunction();
    
    Sequencer& getSequencer() { return sequencer; }
    
    bool modulesLoaded() {
        if (magenta==nullptr)
            return false;
        return true;
    }
    AudioProcessorValueTreeState parameters;
private:
    AudioProcessorValueTreeState::ParameterLayout createLayout();
    
    py::object noteSequenceToPyNoteSequence(NoteSequence n);
    NoteSequence pyNoteSequenceToNoteSequence(py::object p);

    // Sequencer object
    Sequencer sequencer;
    
    // py module for all processing
    PyObject* mainModule;
    
    // python modules
    py::object magenta;
    py::object magentaMusic;
    py::object music_pb2;
    
    std::unique_ptr<NoteSequence> sequence;
    std::unique_ptr<ImportThread> importThread;
    
    // holder for look and feel
    LookAndFeelHolder<MagentaBeatsLookAndFeel> lafHolder;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MagentaBeatsAudioProcessor)
};
