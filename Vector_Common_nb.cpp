#include "Vector_Common_nb.hpp"

void bindBigData(nb::module_ &m, const std::string &pythonName)
{
  nb::class_<BigData>(m, pythonName.c_str()/*, nb::module_local()*/) // https://nanobind.readthedocs.io/en/latest/porting.html#removed-features
    .def(nb::init<>())
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
        { return nb::make_iterator(nb::type<BigData::ArrayType>(), "iterator", d.data.begin(), d.data.end()); },
        nb::keep_alive<0, 1>());
}
