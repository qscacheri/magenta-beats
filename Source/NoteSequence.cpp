

#include "NoteSequence.h"
#include "python_utils.h"

using namespace pybind11::literals;

Array<int> NoteSequence::noteValues({36, 38, 42, 46});

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

int noteSort(const Note &n1, const Note &n2)
{
    return n1.startTime < n2.startTime;
}

NoteSequence::NoteSequence()
{
    notes2.resize(4);
    for (int i = 0; i < 4; i++){
        notes2[i].resize(16);
    }
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

void NoteSequence::addNote(Note n)
{
    notes.push_back(n);
    int which = noteValues.indexOf(n.pitch);
    notes2[which][n.startTime] = n;
}

void NoteSequence::addNote(int pitch, int startTime, int endTime, int velocity)
{
    notes.push_back(Note(pitch, velocity, startTime, endTime));
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

bool NoteSequence::isNotePresent(int pitch, int time)
{
    for (int i = 0; i < notes.size(); i++)
    {
        if (notes[i].pitch == pitch && notes[i].startTime == time)
        {
            return true;
        }
    }
    return false;
}

std::vector<Note> NoteSequence::getNotes()
{
    return notes;
}

ValueTree NoteSequence::toValueTree()
{
    ValueTree tree { "note_sequence", {{ "length", getLength() }},
      {
      }
    };
    
    for (int i = 0; i < getLength(); i++){
        ValueTree noteTree { "Note", {{ "pitch", notes[i].pitch}, { "start_time", notes[i].startTime}, { "velocity", notes[i].velocity}},
          {
          }
        };
        
        tree.addChild(noteTree, -1, nullptr);
    }
    
    return tree;
}

void NoteSequence::fromValueTree(ValueTree tree)
{
    for (int i = 0; i < tree.getNumChildren(); i++){
        
        int pitch = tree.getChild(i).getPropertyAsValue("pitch", nullptr).getValue();
        int velocity = tree.getChild(i).getPropertyAsValue("velocity", nullptr).getValue();
        int startTime = tree.getChild(i).getPropertyAsValue("start_time", nullptr).getValue();
        
        notes.push_back(Note(pitch, velocity, startTime, startTime + 1));
    }
}


double NoteSequence::ppqToSecs(int ppq, int tempo)
{
    return (double)ppq * (15.f / double(tempo));
}

int NoteSequence::ppqToSamples(int ppq, int tempo, double sampleRate)
{
    return ((int)((60.0/tempo*sampleRate) / 4 * ppq));
}

