# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/local/bin/cmake

# The command to remove a file.
RM = /opt/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/quinscacheri/Documents/dev/JUCE Files/Magenta Beats/Source/pybind"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/quinscacheri/Documents/dev/JUCE Files/Magenta Beats/Source/pybind"

# Include any dependencies generated for this target.
include CMakeFiles/example.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/example.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/example.dir/flags.make

CMakeFiles/example.dir/example.cpp.o: CMakeFiles/example.dir/flags.make
CMakeFiles/example.dir/example.cpp.o: example.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/quinscacheri/Documents/dev/JUCE Files/Magenta Beats/Source/pybind/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/example.dir/example.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example.dir/example.cpp.o -c "/Users/quinscacheri/Documents/dev/JUCE Files/Magenta Beats/Source/pybind/example.cpp"

CMakeFiles/example.dir/example.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example.dir/example.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/quinscacheri/Documents/dev/JUCE Files/Magenta Beats/Source/pybind/example.cpp" > CMakeFiles/example.dir/example.cpp.i

CMakeFiles/example.dir/example.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example.dir/example.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/quinscacheri/Documents/dev/JUCE Files/Magenta Beats/Source/pybind/example.cpp" -o CMakeFiles/example.dir/example.cpp.s

# Object files for target example
example_OBJECTS = \
"CMakeFiles/example.dir/example.cpp.o"

# External object files for target example
example_EXTERNAL_OBJECTS =

example.cpython-37m-darwin.so: CMakeFiles/example.dir/example.cpp.o
example.cpython-37m-darwin.so: CMakeFiles/example.dir/build.make
example.cpython-37m-darwin.so: CMakeFiles/example.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/quinscacheri/Documents/dev/JUCE Files/Magenta Beats/Source/pybind/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared module example.cpython-37m-darwin.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/example.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/example.dir/build: example.cpython-37m-darwin.so

.PHONY : CMakeFiles/example.dir/build

CMakeFiles/example.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/example.dir/cmake_clean.cmake
.PHONY : CMakeFiles/example.dir/clean

CMakeFiles/example.dir/depend:
	cd "/Users/quinscacheri/Documents/dev/JUCE Files/Magenta Beats/Source/pybind" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/quinscacheri/Documents/dev/JUCE Files/Magenta Beats/Source/pybind" "/Users/quinscacheri/Documents/dev/JUCE Files/Magenta Beats/Source/pybind" "/Users/quinscacheri/Documents/dev/JUCE Files/Magenta Beats/Source/pybind" "/Users/quinscacheri/Documents/dev/JUCE Files/Magenta Beats/Source/pybind" "/Users/quinscacheri/Documents/dev/JUCE Files/Magenta Beats/Source/pybind/CMakeFiles/example.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/example.dir/depend

