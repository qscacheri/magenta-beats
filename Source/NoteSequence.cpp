

#include "NoteSequence.h"
#include "python_utils.h"


NoteSequence::NoteSequence(PyObject* pyNoteSequence)
{

        if (!PyObject_HasAttrString(pyNoteSequence, "notes"))
                return;

        tempo = getTempo(pyNoteSequence);

        notes = getNotes(pyNoteSequence);

        Py_DECREF(pyNoteSequence);

        std::cout << toString() << '\n';
}

int NoteSequence::getTempo(PyObject* py)
{
        PyObject* pyTempos = PyObject_GetAttrString(py, "tempos");
        PyObject* callable = PyObject_GetAttrString(pyTempos, "__getitem__");
        PyObject* args = Py_BuildValue("(i)", 0);
        return (int)PyLong_AsLong(PyObject_GetAttrString(PyObject_Call(callable, args, NULL),"qpm"));
}

std::vector<Note> NoteSequence::getNotes(PyObject* py)
{
        std::vector<Note> n;

        double start = 0;
        double end = 0;


        PyObject* pyNotes = PyObject_GetAttrString(py, "notes");
        int size = PyLong_AsLong(PyObject_CallMethod(pyNotes, "__len__", NULL));

        //interate through all notes
        for (int i = 0; i < size; i++) {
                PyObject* callable = PyObject_GetAttrString(pyNotes, "__getitem__");
                PyObject* args = Py_BuildValue("(i)", i);
                PyObject* note = PyObject_Call(callable, args, NULL);

                int pitch = PyLong_AsLong(PyObject_GetAttrString(note, "pitch"));
                int velocity = PyLong_AsLong(PyObject_GetAttrString(note, "velocity"));

                start = PyFloat_AsDouble(PyObject_GetAttrString(note, "start_time"));
                end = PyFloat_AsDouble(PyObject_GetAttrString(note, "end_time"));

                n.push_back(Note(pitch, velocity, start, end));

                Py_DECREF(args);
                Py_DECREF(note);
                Py_DECREF(callable);
        }

        return n;
}

std::string NoteSequence::toString()
{
        std::string s;
        for (int i = 0; i < notes.size(); i++)
        {
                s += notes[i].toString();
        }

        return s;
}

PyObject* NoteSequence::createNoteSequence(PyObject* module)
{
    PyObject* pyNoteSequence = PyObject_GetAttrString(module, "sequence");
    python_utils::printPyObject(pyNoteSequence);
    NoteSequence::addNoteToPySequnce(Note(), pyNoteSequence);
    
}

void NoteSequence::addNoteToPySequnce(Note n, PyObject* noteSequence)
{
    PyObject* notes = PyObject_GetAttrString(noteSequence, "notes");
    PyObject* addFunction = PyObject_GetAttrString(notes, "add");
    PyObject* args = Py_BuildValue("(i)", 60);
    PyObject_Call(addFunction, args, NULL);
    
    Py_DecRef(notes);
    Py_DecRef(addFunction);
    Py_DecRef(args);
}
