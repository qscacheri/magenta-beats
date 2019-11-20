# export PYTHONPATH="$PWD"
# g++ -c -Wall -Werror -fpic CppWrapper.cpp -I/usr/local/Cellar/python/3.7.4_1/Frameworks/Python.framework/Versions/3.7/include/python3.7m -I/usr/local/Cellar/python/3.7.4_1/Frameworks/Python.framework/Versions/3.7/include/python3.7m -Wno-unused-result -Wsign-compare -Wunreachable-code -fno-common -dynamic -DNDEBUG -g -fwrapv -O3 -Wall -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/usr/include -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/Tk.framework/Versions/8.5/Headers -I/Users/quinscacheri/Documents/dev/Libraries/boostg




#  # -L/usr/local/opt/python/Frameworks/Python.framework/Versions/3.7/lib/python3.7/config-3.7m-darwin -lpython3.7m -ldl -framework CoreFoundation -I/Users/quinscacheri/Documents/dev/Libraries/boost -L/Users/quinscacheri/Documents/dev/Libraries/boost/stage/lib -lboost_python3

# clang -I /anaconda3/include/python3.7m/ -I  /Users/quinscacheri/Documents/dev/Libraries/pybind11/include NoteSequence.cpp -fpic -c -o NoteSequence.o
# clang -o MagentaBeats.so -shared NoteSequence.o -L/usr/local/opt/python/Frameworks/Python.framework/Versions/3.7/lib/python3.7/config-3.7m-darwin -lpython3.7m
c++ -O3 -Wall -shared -std=c++11 -fPIC -I /Users/quinscacheri/Documents/dev/Libraries/pybind11/include `python-config --cflags --ldflags` NoteSequence.cpp -o Ex.so -L /anaconda3/lib -lpython3.7m
