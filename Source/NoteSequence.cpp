

#include "NoteSequence.h"
#include "python_utils.h"
    
using namespace pybind11::literals;
int NoteSequence::noteValues[8] = {60, 62, 64, 65, 67, 69, 71, 72};

//PYBIND11_MODULE(MagentaBeats, m) {
//
//    py::class_<NoteSequence>(m, "CNoteSequence")
//    .def(py::init<>())
//    .def("test", &NoteSequence::test)
//    .def("getNotes", &NoteSequence::getNotes);
//
//    py::class_<Note>(m, "CNote")
//    .def(py::init<>());
//
//}



NoteSequence::NoteSequence()
{

}

NoteSequence::NoteSequence(PyObject* pyNoteSequence)
{

//    if (!PyObject_HasAttrString(pyNoteSequence, "notes"))
//        return;
//
//    tempo = getTempo(pyNoteSequence);
//
//    notes = notesFromPy(pyNoteSequence);
//
//    Py_DECREF(pyNoteSequence);
//
//    std::cout << toString() << '\n';
}

//int NoteSequence::getTempo(PyObject* py)
//{
//    PyObject* pyTempos = PyObject_GetAttrString(py, "tempos");
//    PyObject* callable = PyObject_GetAttrString(pyTempos, "__getitem__");
//    PyObject* args = Py_BuildValue("(i)", 0);
//    return (int)PyLong_AsLong(PyObject_GetAttrString(PyObject_Call(callable, args, NULL),"qpm"));
//}



std::string NoteSequence::toString()
{
    std::string s;
    for (int i = 0; i < notes.size(); i++)
    {
        s += notes[i].toString();
    }

    return s;
}

void NoteSequence::addNote(Note n)
{
    notes.push_back(n);
}

void NoteSequence::removeNote(int pitch, int time)
{
    for (int i = 0; i < notes.size(); i++){
        if (notes[i].pitch == pitch && notes[i].startTime == time)
        {
            notes.erase(notes.begin()+i);
        }
    }
}

bool NoteSequence::checkAndRemoveNote(int pitch, int time)
{
    for (int i = 0; i < notes.size(); i++)
    {
        if (notes[i].pitch == pitch && notes[i].startTime == time)
        {
            notes.erase(notes.begin()+i);
            return true;
        }
    }
    return false;
}

std::vector<Note> NoteSequence::getNotes()
{
    return notes;
}

double NoteSequence::ppqToSecs(int ppq, int tempo)
{
    return (60000.0 / (tempo * ppq));
}
