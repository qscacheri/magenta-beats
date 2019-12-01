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

    drums.total_time = 1.375
    
    drums.tempos.add(qpm=120)
    drums = mm.quantize_note_sequence(drums, 4)
    mm.sequence_proto_to_midi_file(drums, "primer.mid")
    return drums

def generateNewSequence(input_sequence, temperature, write_to_file):

    input_sequence = mm.quantize_note_sequence(input_sequence, 8)
    bundle = sequence_generator_bundle.read_bundle_file('/Users/quinscacheri/Documents/dev/JUCE Files/Magenta Beats/Source/python/drum_kit_rnn.mag')
    generator_map = drums_rnn_sequence_generator.get_generator_map()
    drum_rnn = generator_map['drum_kit'](checkpoint=None, bundle=bundle)
    drum_rnn.initialize()

    qpm = input_sequence.tempos[0].qpm
    last_end_time = (max(n.end_time for n in input_sequence.notes)
                      if input_sequence.notes else 0)
#    total_seconds = num_steps * input_sequence.quantization_info.steps_per_quarter;
    
    generator_options = generator_pb2.GeneratorOptions()
    generator_options.args['temperature'].float_value = temperature
    generate_section = generator_options.generate_sections.add(start_time=last_end_time, end_time=8.0)

    new_sequence = drum_rnn.generate(input_sequence, generator_options)
    new_sequence = mm.trim_note_sequence(new_sequence, 2.0, 4.0)
    new_sequence = mm.quantize_note_sequence(new_sequence, 4)
#
#    new_sequence.quantization_info.steps_per_quarter = 8

    
    if (True):
        mm.sequence_proto_to_midi_file(input_sequence, 'primer.mid')
        mm.sequence_proto_to_midi_file(new_sequence, 'new_sequence.mid')

    return new_sequence
