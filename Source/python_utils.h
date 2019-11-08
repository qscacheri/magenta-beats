#ifndef PY_UTILS_H
#define PY_UTILS_H


#include "Python.h"
#include <string>

namespace python_utils
{
void printPyObject(PyObject* py);

std::string getPyObjectType(PyObject* py);

PyObject* importModuleString(char* s);
}

#endif
