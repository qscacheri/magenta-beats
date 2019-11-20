cdef extern from "../NoteSequence.cpp":
    pass

# Declare the class with cdef
cdef extern from "Rectangle.h" namespace "shapes":
    cdef cppclass Rectangle:
        NoteSequence() except +
        int test()
