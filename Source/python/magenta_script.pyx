# import libraries
# import magenta.music as mm
# import magenta
# import tensorflow
# # from distutils.core cimport setup
# # from distutils.extension import Extension
# from magenta.protobuf import music_pb2

cdef public wrapTest():
    cdef int x = 5
    return x

def test():
    return 1

def testObject(obj):
    return repr(obj)

#
# def create():
#     twinkle_twinkle = music_pb2.NoteSequence()
#
#     # Add the notes to the sequence.
#     twinkle_twinkle.notes.add(pitch=60, start_time=0.0, end_time=0.5, velocity=80)
#     twinkle_twinkle.notes.add(pitch=60, start_time=0.5, end_time=1.0, velocity=80)
#     twinkle_twinkle.notes.add(pitch=67, start_time=1.0, end_time=1.5, velocity=80)
#     twinkle_twinkle.notes.add(pitch=67, start_time=1.5, end_time=2.0, velocity=80)
#     twinkle_twinkle.notes.add(pitch=69, start_time=2.0, end_time=2.5, velocity=80)
#     twinkle_twinkle.notes.add(pitch=69, start_time=2.5, end_time=3.0, velocity=80)
#     twinkle_twinkle.notes.add(pitch=67, start_time=3.0, end_time=4.0, velocity=80)
#     twinkle_twinkle.notes.add(pitch=65, start_time=4.0, end_time=4.5, velocity=80)
#     twinkle_twinkle.notes.add(pitch=65, start_time=4.5, end_time=5.0, velocity=80)
#     twinkle_twinkle.notes.add(pitch=64, start_time=5.0, end_time=5.5, velocity=80)
#     twinkle_twinkle.notes.add(pitch=64, start_time=5.5, end_time=6.0, velocity=80)
#     twinkle_twinkle.notes.add(pitch=62, start_time=6.0, end_time=6.5, velocity=80)
#     twinkle_twinkle.notes.add(pitch=62, start_time=6.5, end_time=7.0, velocity=80)
#     twinkle_twinkle.notes.add(pitch=60, start_time=7.0, end_time=8.0, velocity=80)
#     twinkle_twinkle.total_time = 8
#     twinkle_twinkle.tempos.add(qpm=60);
#     noteList = music_pb2.NoteSequence.SerializeToString(twinkle_twinkle)
#
#     return twinkle_twinkle
