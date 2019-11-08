#include <iostream>
#include "python_utils.h"

namespace python_utils
{
void printPyObject(PyObject* py)
{
        if (py == NULL)
        {
                printf("PyObject is NULL\n");
                return;
        }
        printf("%s\n", PyUnicode_AsUTF8AndSize(PyObject_Repr(py), NULL));
}

std::string getPyObjectType(PyObject* py)
{
        PyTypeObject* type = py->ob_type;
        const char* p = type->tp_name;
        return std::string(p);
}

PyObject* importModuleString(char* s)
{
        PyObject* module = PyImport_Import(PyUnicode_DecodeFSDefault(s));
        if (module == NULL)
        {
                std::cout << "CANNOT LOAD MODULE" << s <<'\n';
                return nullptr;
        }

        return module;
}

}
