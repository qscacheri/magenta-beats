from libcpp.vector cimport vector

cdef extern from "../NoteSequence.h" namespace "magentaBeats":
    cdef cppclass NoteSequence:

from NoteSequence cimport NoteSequence

# Create a Cython extension type which holds a C++ instance
# as an attribute and create a bunch of forwarding methods
# Python extension type.

cdef class PyNoteSequence:
    cdef NoteSequence cppNoteSequence

    def __cinit__(self):
        self.cppNoteSequence = NoteSequence()

    def pyTest()
        return self.cppNoteSequence.test()
