#ifndef NOTE_SEQUENCE_H
#define NOTE_SEQUENCE_H

#include <Python.h>
#include "Note.h"
#include <vector>
#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <array>
#include "JuceHeader.h"

namespace py = pybind11;

class NoteSequence
{
public:
//    static int noteValues[8];
    static Array<int> noteValues;
    NoteSequence();
        
    int getTempo() { return tempo; }

    int getLength() { return notes.size(); }
    
    void addNote(Note n);
    void addNote(int pitch, int startTime, int endTime, int velocity = 100);
    void removeNote(int pitch, int time);
    
    bool isNotePresent(int pitch, int time);
    bool checkAndRemoveNote(int pitch, int time);
    
    
    std::vector<Note> getNotes();
        
    std::string toString();
    
    ValueTree toValueTree();
    void fromValueTree(ValueTree);

    static double ppqToSecs(int ppq, int tempo);
    static int ppqToSamples(int ppq, int tempo, double sampleRate);
    
    

private:
    int tempo = 120;
    std::vector<Note> notes;
    Array<Array<Note>> notes2;
    
};
#endif
