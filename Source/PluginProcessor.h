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
    enum SequencerType : int
    {
        userSeq = 0,
        magentaSeq
    };
    
    
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
    
    Sequencer& getSequencer(SequencerType which) {
        if (which == SequencerType::userSeq)
            return userSequencer;
        return magentaSequencer;
    }
    
    bool areModulesLoaded() {
        return modulesLoaded;
    }
    
    void setSelectedSequencer(int which) { selectedSequencer = which; }

    NoteSequence applyModel();

    AudioProcessorValueTreeState parameters;
    
    float temperatureParam = 1;
    
    
private:
    
    void importModules();
    
    AudioProcessorValueTreeState::ParameterLayout createLayout();
    
    py::object noteSequenceToPyNoteSequence(NoteSequence n);
    NoteSequence* pyNoteSequenceToNoteSequence(py::object p);

    
    void initializeModel();
    
    int selectedSequencer = SequencerType::userSeq;

    // Sequencer object
    Sequencer userSequencer;
    Sequencer magentaSequencer;

    // py module for all processing
    PyObject* mainModule;
    
    // python modules
    py::object magenta;
    py::object magentaMusic;
    py::object music_pb2;
    py::object melody_rnn_sequence_generator;
    py::object sequence_generator_bundle;
    py::object generator_pb2;
    
    // python objects
    py::object bundle;
    py::object generator_map;
    py::object melody_rnn;
    
    py::object magenta_beats;
    
    std::unique_ptr<ImportThread> importThread;
    
    bool modulesLoaded = false;
    
    // holder for look and feel
    LookAndFeelHolder<MagentaBeatsLookAndFeel> lafHolder;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MagentaBeatsAudioProcessor)
};
