#distutils: language = c++

from NoteSequence cimport NoteSequence

def main():
    seq = new NoteSequence()
    try:
        test = seq.test()
    finally:
        del seq
    cdef Rectangle rec_stack
