#include "Vector_Common_py.hpp"

void bindBigData(py::module &m, const std::string &pythonName)
{
  py::class_<BigData>(m, pythonName.c_str(), py::module_local())
    .def(py::init<>())
    .def("__eq__", [](const BigData &d1, BigData &d2)
          {
            for(size_t i = 0; i < d1.data.size(); ++i)
              if(d1.data[i] != d2.data[i])
                return false;
            return true; })
    .def("__getitem__", [](const BigData &d, size_t idx)
          { return d.data[idx]; })
    .def("__setitem__", [](BigData &d, size_t idx, uint8_t val)
          {
            d.data[idx] = val;
          })
    .def(
        "__iter__", [](BigData &d)
        { return py::make_iterator(d.data.begin(), d.data.end()); },
        py::keep_alive<0, 1>());
}
