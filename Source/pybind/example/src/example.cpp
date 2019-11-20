#include <iostream>
#include <pybind11/pybind11.h>
namespace py = pybind11;

class ExampleClass
{
public:
ExampleClass()
{

}
void test()
{
        std::cout<<"Testing..."<<"\n";
}
};


PYBIND11_MODULE(example, m) {
        py::class_<ExampleClass>(m, "ExampleClass")
        .def(py::init<>())
        .def("test", &ExampleClass::test);
}
