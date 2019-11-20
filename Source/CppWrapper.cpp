#include  <iostream>
#include "NoteSequence.h"
#include <boost/python.hpp>
using namespace boost::python;

BOOST_PYTHON_MODULE(MagentaBeats)
{
    class_<NoteSequence>("CppNoteSequence")
    .def("test", &NoteSequence::test);
}
