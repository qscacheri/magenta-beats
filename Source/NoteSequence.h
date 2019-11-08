#ifndef NOTE_SEQUENCE_H
#define NOTE_SEQUENCE_H

#include <Python.h>
#include "Note.h"
#include <vector>
#include <iostream>

class NoteSequence
{
public:
    NoteSequence(PyObject* pyNoteSequence);
    
    int getTempo(PyObject* py);
    
    std::vector<Note> getNotes(PyObject* py);
    
    std::string toString();
    
    static PyObject* createNoteSequence(PyObject* module);
    
    static void addNoteToPySequnce(Note n, PyObject* pb2);
private:
    
    int tempo;
    std::vector<Note> notes;
    
    
};

#endif
