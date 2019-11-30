import magenta
from magenta.protobuf import music_pb2
from magenta.models.melody_rnn import melody_rnn_sequence_generator
from magenta.music import sequence_generator_bundle
from magenta.protobuf import generator_pb2
from magenta.protobuf import music_pb2
import magenta.music as mm

from magenta.models.drums_rnn import drums_rnn_sequence_generator
from magenta.models.drums_rnn import drums_rnn_generate
from magenta.models.drums_rnn import drums_rnn_model

def createDrumTrack():
    drums = music_pb2.NoteSequence()
    drums.notes.add(pitch=36, start_time=0, end_time=0.125, is_drum=True, instrument=10, velocity=80)
    drums.notes.add(pitch=38, start_time=0, end_time=0.125, is_drum=True, instrument=10, velocity=80)
    drums.notes.add(pitch=42, start_time=0, end_time=0.125, is_drum=True, instrument=10, velocity=80)
    drums.notes.add(pitch=46, start_time=0, end_time=0.125, is_drum=True, instrument=10, velocity=80)
    drums.notes.add(pitch=42, start_time=0.25, end_time=0.375, is_drum=True, instrument=10, velocity=80)
    drums.notes.add(pitch=42, start_time=0.375, end_time=0.5, is_drum=True, instrument=10, velocity=80)
    drums.notes.add(pitch=42, start_time=0.5, end_time=0.625, is_drum=True, instrument=10, velocity=80)
    drums.notes.add(pitch=50, start_time=0.5, end_time=0.625, is_drum=True, instrument=10, velocity=80)
    drums.notes.add(pitch=36, start_time=0.75, end_time=0.875, is_drum=True, instrument=10, velocity=80)
    drums.notes.add(pitch=38, start_time=0.75, end_time=0.875, is_drum=True, instrument=10, velocity=80)
    drums.notes.add(pitch=42, start_time=0.75, end_time=0.875, is_drum=True, instrument=10, velocity=80)
    drums.notes.add(pitch=45, start_time=0.75, end_time=0.875, is_drum=True, instrument=10, velocity=80)
    drums.notes.add(pitch=36, start_time=1, end_time=1.125, is_drum=True, instrument=10, velocity=80)
    drums.notes.add(pitch=42, start_time=1, end_time=1.125, is_drum=True, instrument=10, velocity=80)
    drums.notes.add(pitch=46, start_time=1, end_time=1.125, is_drum=True, instrument=10, velocity=80)
    drums.notes.add(pitch=42, start_time=1.25, end_time=1.375, is_drum=True, instrument=10, velocity=80)
    drums.notes.add(pitch=48, start_time=1.25, end_time=1.375, is_drum=True, instrument=10, velocity=80)
    drums.notes.add(pitch=50, start_time=1.25, end_time=1.375, is_drum=True, instrument=10, velocity=80)
    drums.time_signatures.add(numerator = 4, denominator = 4)
    drums.time_signatures[0].numerator = 4
    drums.time_signatures[0].denominator = 4
    drums.tempos.add(qpm=60)
    drums.quantization_info.steps_per_quarter = 4
    return drums

def createDrums():
    drums = music_pb2.NoteSequence()

    drums.notes.add(pitch=36, start_time=0, end_time=0.125, is_drum=True, instrument=10, velocity=80)

    drums.notes.add(pitch=42, start_time=0, end_time=0.125, is_drum=True, instrument=10, velocity=80)
    drums.notes.add(pitch=42, start_time=0.125, end_time=0.25, is_drum=True, instrument=10, velocity=80)
    drums.notes.add(pitch=42, start_time=.25, end_time=0.375, is_drum=True, instrument=10, velocity=80)
    drums.notes.add(pitch=42, start_time=0.375, end_time=0.5, is_drum=True, instrument=10, velocity=80)

    drums.notes.add(pitch=38, start_time=0.5, end_time=0.625, is_drum=True, instrument=10, velocity=80)

    drums.notes.add(pitch=42, start_time=.625, end_time=0.75, is_drum=True, instrument=10, velocity=80)
    drums.notes.add(pitch=42, start_time=0.75, end_time=0.875, is_drum=True, instrument=10, velocity=80)
    drums.notes.add(pitch=42, start_time=.875, end_time=1.0, is_drum=True, instrument=10, velocity=80)

    drums.notes.add(pitch=36, start_time=1.0, end_time=1.125, is_drum=True, instrument=10, velocity=80)
    drums.notes.add(pitch=42, start_time=1, end_time=1.125, is_drum=True, instrument=10, velocity=80)
    drums.notes.add(pitch=42, start_time=1.125, end_time=1.25, is_drum=True, instrument=10, velocity=80)
    drums.notes.add(pitch=42, start_time=1.25, end_time=1.375, is_drum=True, instrument=10, velocity=80)
    drums.notes.add(pitch=42, start_time=1.375, end_time=1.5, is_drum=True, instrument=10, velocity=80)
    drums.time_signatures.add(numerator = 4, denominator = 4)
    drums.time_signatures[0].numerator = 4
    drums.time_signatures[0].denominator = 4
    drums.tempos.add(qpm=60)
    drums.quantization_info.steps_per_quarter = 4

    drums.total_time = 1.375

    drums.tempos.add(qpm=60)
    drums = mm.quantize_note_sequence(drums, 8)
    return drums


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

    mm.sequence_proto_to_midi_file(sequence, 'twinkleExtended.mid')

def extendDrums():
    dt = createDrumTrack()
    print("Initializing Drums RNN...")
    bundle = sequence_generator_bundle.read_bundle_file('drum_kit_rnn.mag')
    generator_map = drums_rnn_sequence_generator.get_generator_map()
    drum_rnn = generator_map['drum_kit'](checkpoint=None, bundle=bundle)
    drum_rnn.initialize()

    input_sequence = drums # change this to teapot if you want
    num_steps = 128 # change this for shorter or longer sequences
    temperature = 1.0 # the higher the temperature the more random the sequence.

    # Set the start time to begin on the next step after the last note ends.
    # new_start_time =
    generator_options = generator_pb2.GeneratorOptions()
    # generator_options.args['primer_sequence'].string_value = "drums.mid"
    generate_section = generator_options.generate_sections.add(start_time=last_end_time + seconds_per_step, end_time=total_seconds)

    # Ask the model to continue the sequence.
    drum_rnn.generateDrumTrack(128, )
    # mm.sequence_proto_to_midi_file(drums, 'drums.mid')
    # mm.sequence_proto_to_midi_file(sequence, 'extendedDrums.mid')

def generateNewSequence(input_sequence, num_steps, temperature, write_to_file = False):

    input_sequence = mm.quantize_note_sequence(input_sequence, 8)
    bundle = sequence_generator_bundle.read_bundle_file('drum_kit_rnn.mag')
    generator_map = drums_rnn_sequence_generator.get_generator_map()
    drum_rnn = generator_map['drum_kit'](checkpoint=None, bundle=bundle)
    drum_rnn.initialize()

    qpm = input_sequence.tempos[0].qpm
    last_end_time = (max(n.end_time for n in input_sequence.notes)
                      if input_sequence.notes else 0)
    total_seconds = num_steps * input_sequence.quantization_info.steps_per_quarter;

    generator_options = generator_pb2.GeneratorOptions()
    generator_options.args['temperature'].float_value = temperature
    generate_section = generator_options.generate_sections.add(start_time=last_end_time, end_time=total_seconds)

    new_sequence = drum_rnn.generate(input_sequence, generator_options)
    new_sequence.quantization_info.steps_per_quarter = 8
    mm.quantize_note_sequence(new_sequence, 8)

    if (write_to_file == True):
        mm.sequence_proto_to_midi_file(input_sequence, 'oldSequence.mid')
        mm.sequence_proto_to_midi_file(new_sequence, 'newSequence.mid')

    return new_sequence
