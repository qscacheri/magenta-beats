#include <iostream>
#include <pybind11/pybind11.h>
namespace py = pybind11;

class ExampleClass
{
public:
Example()
{

}
void test()
{
        std::cout<<"Testing..."<<"\n";
}
};


PYBIND11_MODULE(example, m) {
        py::class_<ExampleClass>(m, "ExampleClass")
        .def("test", &Example::test);
}
