#ifndef NOTE_SEQUENCE_H
#define NOTE_SEQUENCE_H

#include <Python.h>
#include "Note.h"
#include <vector>
#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

class NoteSequence
{
public:
    static int noteValues[8];

    NoteSequence();
    
    NoteSequence(PyObject* pyNoteSequence);
    
    int getTempo() { return tempo; }

    void addNote(Note n);
    void removeNote(int pitch, int time);
    
    bool checkAndRemoveNote(int pitch, int time);
    
    std::vector<Note> getNotes();
        
    std::string toString();
    
    static double ppqToSecs(int ppq, int tempo);
private:
    int tempo = 120;
    std::vector<Note> notes;
    
    
};
#endif
