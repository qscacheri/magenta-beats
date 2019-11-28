import magenta
from magenta.protobuf import music_pb2
from magenta.models.melody_rnn import melody_rnn_sequence_generator
from magenta.music import sequence_generator_bundle
from magenta.protobuf import generator_pb2
from magenta.protobuf import music_pb2
import magenta.music as mm

def createTwinkle():
    twinkle_twinkle = music_pb2.NoteSequence()
    twinkle_twinkle.notes.add(pitch=60, start_time=0.0, end_time=0.5, velocity=80)
    twinkle_twinkle.notes.add(pitch=60, start_time=0.5, end_time=1.0, velocity=80)
    twinkle_twinkle.notes.add(pitch=67, start_time=1.0, end_time=1.5, velocity=80)
    twinkle_twinkle.notes.add(pitch=67, start_time=1.5, end_time=2.0, velocity=80)
    twinkle_twinkle.notes.add(pitch=69, start_time=2.0, end_time=2.5, velocity=80)
    twinkle_twinkle.notes.add(pitch=69, start_time=2.5, end_time=3.0, velocity=80)
    twinkle_twinkle.notes.add(pitch=67, start_time=3.0, end_time=4.0, velocity=80)
    twinkle_twinkle.notes.add(pitch=65, start_time=4.0, end_time=4.5, velocity=80)
    twinkle_twinkle.notes.add(pitch=65, start_time=4.5, end_time=5.0, velocity=80)
    twinkle_twinkle.notes.add(pitch=64, start_time=5.0, end_time=5.5, velocity=80)
    twinkle_twinkle.notes.add(pitch=64, start_time=5.5, end_time=6.0, velocity=80)
    twinkle_twinkle.notes.add(pitch=62, start_time=6.0, end_time=6.5, velocity=80)
    twinkle_twinkle.notes.add(pitch=62, start_time=6.5, end_time=7.0, velocity=80)
    twinkle_twinkle.notes.add(pitch=60, start_time=7.0, end_time=8.0, velocity=80)
    twinkle_twinkle.total_time = 8

    twinkle_twinkle.tempos.add(qpm=60);

    return twinkle_twinkle

def extendTwinkle():
    twinkle_twinkle = createTwinkle()
    print("Initializing Melody RNN...")
    bundle = sequence_generator_bundle.read_bundle_file('./basic_rnn.mag')
    generator_map = melody_rnn_sequence_generator.get_generator_map()
    melody_rnn = generator_map['basic_rnn'](checkpoint=None, bundle=bundle)
    melody_rnn.initialize()

    input_sequence = twinkle_twinkle # change this to teapot if you want
    num_steps = 128 # change this for shorter or longer sequences
    temperature = 1.0 # the higher the temperature the more random the sequence.

    # Set the start time to begin on the next step after the last note ends.
    last_end_time = (max(n.end_time for n in input_sequence.notes)
                      if input_sequence.notes else 0)
    qpm = input_sequence.tempos[0].qpm
    seconds_per_step = 60.0 / qpm / melody_rnn.steps_per_quarter
    total_seconds = num_steps * seconds_per_step

    generator_options = generator_pb2.GeneratorOptions()
    generator_options.args['temperature'].float_value = temperature
    generate_section = generator_options.generate_sections.add(start_time=last_end_time + seconds_per_step, end_time=total_seconds)

    # Ask the model to continue the sequence.
    sequence = melody_rnn.generate(input_sequence, generator_options)

    mm.sequence_proto_to_midi_file(sequence, 'extended.mid')

def test(t):
    return 10

def generateNewSequence(input_sequence, num_steps, temperature):
    temperature = 1.0
    print("testingtesting")
    bundle = sequence_generator_bundle.read_bundle_file('/Users/quinscacheri/Documents/dev/JUCE Files/Magenta Beats/testing/basic_rnn.mag')
    generator_map = melody_rnn_sequence_generator.get_generator_map()
    melody_rnn = generator_map['basic_rnn'](checkpoint=None, bundle=bundle)
    melody_rnn.initialize()

    qpm = input_sequence.tempos[0].qpm
    seconds_per_step = 60.0 / qpm / melody_rnn.steps_per_quarter
    last_end_time = 9
    total_seconds = num_steps * seconds_per_step

    generator_options = generator_pb2.GeneratorOptions()
    generator_options.args['temperature'].float_value = temperature
    generate_section = generator_options.generate_sections.add(start_time=last_end_time, end_time=total_seconds)

    newSequence = melody_rnn.generate(input_sequence, generator_options)
    return newSequence
