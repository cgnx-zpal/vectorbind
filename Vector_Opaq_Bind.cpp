#include "Vector_Common_py.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>

#include <vector>

PYBIND11_MAKE_OPAQUE(BigData);
PYBIND11_MAKE_OPAQUE(foo<int>);
PYBIND11_MAKE_OPAQUE(foo<BigData>);
PYBIND11_MAKE_OPAQUE(std::vector<int>);
PYBIND11_MAKE_OPAQUE(std::vector<BigData>);

namespace py = pybind11;

PYBIND11_MODULE(Vector_Opaq_Bind, m) {
  m.def("increase_i", &increase<int>, "A function that increase the elements of a vector");
  m.def("increase_b", &increase<BigData>, "A function that increase the elements of a vector");
  m.def("append_1i", &append1<int>, "A function that appends value 1 to the vector");
  m.def("append_1b", &append1<BigData>, "A function that appends value 1 to the vector");
  m.def("get_b", &getBigData, "Returns an item in BigData");
  bindBigData(m, "BigData");
  py::bind_vector<std::vector<int>>(m, "VectorInt");
  py::bind_vector<std::vector<BigData>>(m, "VectorBigData");
  py::implicitly_convertible<py::list, std::vector<int>>();
  py::implicitly_convertible<py::list, std::vector<BigData>>();
  fooClass<int>(m, "FooInt");
  fooClass<BigData>(m, "FooBigData");
}
