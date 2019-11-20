#ifndef NOTE_SEQUENCE_H
#define NOTE_SEQUENCE_H

#include <Python.h>
#include "Note.h"
#include <vector>
#include <iostream>
class NoteSequence
{
public:
NoteSequence();

NoteSequence(PyObject* pyNoteSequence);

int getTempo(PyObject* py);

std::vector<Note> getNotes(PyObject* py);

std::string toString();

void test();

static PyObject* createNoteSequence(PyObject* module);

static void addNoteToPySequnce(Note n, PyObject* pb2);

int tempo;
std::vector<Note> notes;


};

#endif
