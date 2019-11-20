
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
//    magenta = py::module::import("magenta");
//    magentaMusic = magenta.attr("music");
//    music_pb2 = magenta.attr("protobuf").attr("music_pb2");
//    py::object n = music_pb2.attr("NoteSequence");
    
//    PyRun_SimpleString("import sys\n");
//    PyRun_SimpleString("sys.path.insert(0, \"/Users/quinscacheri/Documents/dev/JUCE Files/Magenta Beats/Source/python\")\n");
//    importThread.reset(new ImportThread("magenta_beats", mainModule, "import"));
//    importThread->startThread();
//    mainModule = PyImport_Import(PyUnicode_DecodeFSDefault("magenta_beats"));
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
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
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
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MagentaBeatsAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void MagentaBeatsAudioProcessor::runFunction()
{
    
}

py::object MagentaBeatsAudioProcessor::noteSequenceToPyNoteSequence(NoteSequence n)
{
    int tempo = n.getTempo();
    py::object pyNoteSequence = music_pb2.attr("NoteSequence");
    auto notes = n.getNotes();
    for (int i = 0; i < notes.size(); i++){
        pyNoteSequence.attr("add")("pitch"_a=60);
    }
    return pyNoteSequence;
    
}

NoteSequence MagentaBeatsAudioProcessor::pyNoteSequenceToNoteSequence(py::object p)
{
    return NoteSequence();
}

AudioProcessorValueTreeState::ParameterLayout MagentaBeatsAudioProcessor::createLayout()
{
    AudioProcessorValueTreeState::ParameterLayout layout;
    return layout;
}



//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MagentaBeatsAudioProcessor();
}
