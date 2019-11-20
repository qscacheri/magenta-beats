cmake_minimum_required(VERSION 3.0)
set (CMAKE_CXX_STANDARD 17)
project(MagentaBeats)
add_subdirectory(pybind11)
pybind11_add_module(MagentaBeats /Users/quinscacheri/Documents/dev/JUCE\ Files/Magenta\ Beats/Source/NoteSequence.cpp)

