
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <cstring>
#include <string>
#include "ImportThread.h"
#include "python_utils.h"

//==============================================================================
MagentaBeatsAudioProcessor::MagentaBeatsAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), parameters(*this, nullptr, "PARAMETERS", createLayout())
#endif
{
    
    Py_Initialize();
}

MagentaBeatsAudioProcessor::~MagentaBeatsAudioProcessor()
{
    
}

//==============================================================================
const String MagentaBeatsAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MagentaBeatsAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MagentaBeatsAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MagentaBeatsAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MagentaBeatsAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MagentaBeatsAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MagentaBeatsAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MagentaBeatsAudioProcessor::setCurrentProgram (int index)
{
}

const String MagentaBeatsAudioProcessor::getProgramName (int index)
{
    return {};
}

void MagentaBeatsAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MagentaBeatsAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    userSequencer.prepareToPlay(sampleRate);
    magentaSequencer.prepareToPlay(sampleRate);

}

void MagentaBeatsAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MagentaBeatsAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MagentaBeatsAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    if (selectedSequencer == SequencerType::userSeq)
        userSequencer.processBlock(getPlayHead(), buffer, midiMessages);
    else
        magentaSequencer.processBlock(getPlayHead(), buffer, midiMessages);

}

//==============================================================================
bool MagentaBeatsAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MagentaBeatsAudioProcessor::createEditor()
{
    return new MagentaBeatsAudioProcessorEditor (*this);
}

//==============================================================================
void MagentaBeatsAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    auto state = parameters.copyState();
    if (state.hasType("note_sequence"))
        state.getChildWithName("note_sequence").copyPropertiesFrom(userSequencer.getStateInformation(), nullptr);
    
    else
        state.addChild(userSequencer.getStateInformation(), -1, nullptr);
    
    std::unique_ptr<XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void MagentaBeatsAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (parameters.state.getType()))
            parameters.replaceState (ValueTree::fromXml (*xmlState));
    DBG(ValueTree::fromXml (*xmlState).toXmlString());

    ValueTree sequence = ValueTree::fromXml (*xmlState).getChildWithName("note_sequence");
    userSequencer.setStateInformation(sequence);
}

void MagentaBeatsAudioProcessor::runFunction()
{
    
}

py::object MagentaBeatsAudioProcessor::noteSequenceToPyNoteSequence(NoteSequence n)
{
    py::object pyNoteSequence = music_pb2.attr("NoteSequence")();
    auto notes = n.getNotes();
    for (int i = 0; i < notes.size(); i++){
        int pitch = notes[i].pitch;
        int velocity = notes[i].velocity;
        double startTime = NoteSequence::ppqToSecs(notes[i].startTime, 120);
        double endTime = NoteSequence::ppqToSecs(notes[i].startTime + 1, 120);
        DBG(startTime);
        pyNoteSequence.attr("notes").attr("add")("pitch"_a=pitch, "velocity"_a=velocity, "start_time"_a = startTime, "end_time"_a = endTime, "is_drum"_a=true);
        
    }
    pyNoteSequence.attr("tempos").attr("add")("qpm"_a = 120);
    pyNoteSequence.attr("total_time") = NoteSequence::ppqToSecs(16, 120);

    py::print(py::str(pyNoteSequence.attr("__str__")()));
    return pyNoteSequence;
    
}

NoteSequence* MagentaBeatsAudioProcessor::pyNoteSequenceToNoteSequence(py::object p)
{
    NoteSequence* n = new NoteSequence();
    
    int numNotes = int(py::int_(p.attr("notes").attr("__len__")()));
    int pitch, velocity, startTime, endTime;
    
    for (int i = 0; i < numNotes; i++){
        py::object note = p.attr("notes").attr("__getitem__")(i);
        pitch = int(py::int_(note.attr("pitch")));
        velocity = int(py::int_(note.attr("velocity")));
        startTime = int(py::int_(note.attr("quantized_start_step"))) % 16;
        endTime = int(py::int_(note.attr("quantized_end_step"))) % 16;
        py::print(py::str(note));
        n->addNote(Note(pitch, velocity, startTime, endTime));
    }
    return n;
}

AudioProcessorValueTreeState::ParameterLayout MagentaBeatsAudioProcessor::createLayout()
{
    AudioProcessorValueTreeState::ParameterLayout layout;
    return layout;
}

void MagentaBeatsAudioProcessor::initializeModel()
{
    /*
     # Import dependencies.
     from magenta.models.melody_rnn import melody_rnn_sequence_generator
     from magenta.music import sequence_generator_bundle
     from magenta.protobuf import generator_pb2
     from magenta.protobuf import music_pb2
     */
        
    py::object util = py::module::import("importlib").attr("util");
    py::object spec = util.attr("spec_from_file_location")("melody_rnn_sequence_generator", "/usr/local/lib/python3.7/site-packages/magenta/models/melody_rnn/melody_rnn_sequence_generator.py");
    py::object models = util.attr("module_from_spec")(spec);
//    melody_rnn_sequence_generator = py::module::import("magenta").attr("models");
    py::print(py::str(models.attr("__dir__")()));
    sequence_generator_bundle =  py::module::import("magenta").attr("models").attr("protobuf").attr("sequence_generator_bundle");

    generator_pb2 = py::module::import("magenta").attr("music").attr("protobuf").attr("generator_pb2");

    /*
    # Initialize the model.
    print("Initializing Melody RNN...")
    bundle = sequence_generator_bundle.read_bundle_file('/content/basic_rnn.mag')
    generator_map = melody_rnn_sequence_generator.get_generator_map()
    melody_rnn = generator_map['basic_rnn'](checkpoint=None, bundle=bundle)
    *melody_rnn = generator_map.__getitem__('basic_rnn')(checkpoint=None, bundle=bundle)

    melody_rnn.initialize()
     */
    
    DBG("Initializing Melody RNN...");
    bundle = sequence_generator_bundle.attr("read_bundle_file")("/Users/quinscacheri/Documents/dev/JUCE Files/Magenta Beats/models/basic_rnn.mag");
    generator_map = melody_rnn_sequence_generator.attr("get_generator_map")();
    melody_rnn = generator_map.attr("__getitem__")("basic_rnn").attr("__call__")("bundle"_a="bundle", "checkpoint"_a="None");

}

NoteSequence MagentaBeatsAudioProcessor::applyModel()
{
    
    if (!modulesLoaded)
        importModules();
        
    py::object sequence = noteSequenceToPyNoteSequence(*userSequencer.getNoteSequence());
    py::print(py::str(sequence.attr("__str__")()));
    
    py::print(py::str(magenta_beats.attr("generateNewSequence").attr("__str__")()));
    py::object newSequence = magenta_beats.attr("generateNewSequence")(sequence, temperatureParam, 1);
    py::print(py::str(newSequence.attr("__str__")()));
    
    magentaSequencer.setNewSequence(pyNoteSequenceToNoteSequence(newSequence));
    return *pyNoteSequenceToNoteSequence(newSequence);
}

void MagentaBeatsAudioProcessor::importModules()
{
    magenta = py::module::import("magenta");
    magentaMusic = magenta.attr("music");
    music_pb2 = magenta.attr("protobuf").attr("music_pb2");
    
    PyRun_SimpleString("import sys\n");
    PyRun_SimpleString("sys.path.insert(0, \"/Users/quinscacheri/Documents/dev/JUCE Files/Magenta Beats/Source/python\")\n");
    magenta_beats = py::module::import("magenta_beats");
    
    modulesLoaded = true;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MagentaBeatsAudioProcessor();
}
