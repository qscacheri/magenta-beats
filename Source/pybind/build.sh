c++ -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` -lpython3.7m example.cpp -o example`python3-config --extension-suffix`
