/*
  ==============================================================================

    ImportThread.h
    Created: 8 Nov 2019 7:59:51pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include <Python.h>

class ImportThread : public Thread
{
public:
    ImportThread(String moduleToImport, PyObject* resultLocation, const String& name, size_t threadStackSize = 0);
    
    virtual void run() override
    {
        result = PyImport_Import(PyUnicode_DecodeFSDefault(moduleName.toUTF8()));
    }
    
private:
    PyObject* result;
    String moduleName;
};
