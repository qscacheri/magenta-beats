/*
  ==============================================================================

    ImportThread.cpp
    Created: 8 Nov 2019 7:59:51pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#include "ImportThread.h"

ImportThread::ImportThread(String moduleToImport, PyObject* resultLocation, const String& name, size_t threadStackSize) : Thread(name, threadStackSize)
{
    moduleName = moduleToImport;
    result = resultLocation;
    
}
