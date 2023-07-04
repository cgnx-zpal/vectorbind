#include "Vector_Common_nb.hpp"

#include <nanobind/nanobind.h>
#include <nanobind/stl/bind_vector.h>

#include <vector>

namespace nb = nanobind;

NB_MODULE(Vector_Nano_Bind, m) {
  m.def("increase_i", &increase<int>, "A function that increase the elements of a vector");
  m.def("increase_b", &increase<BigData>, "A function that increase the elements of a vector");
  m.def("append_1i", &append1<int>, "A function that appends value 1 to the vector");
  m.def("append_1b", &append1<BigData>, "A function that appends value 1 to the vector");
  m.def("get_b", &getBigData, "Returns an item in BigData");
  bindBigData(m, "BigData");
  nb::bind_vector<std::vector<int>>(m, "VectorInt");
  nb::bind_vector<std::vector<BigData>>(m, "VectorBigData");
  fooClass<int>(m, "FooInt");
  fooClass<BigData>(m, "FooBigData");
}