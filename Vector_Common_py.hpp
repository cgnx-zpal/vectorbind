#include "Vector_Common.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>

#include <vector>

namespace py = pybind11;

extern void bindBigData(py::module &m, const std::string &pythonName);

template <typename T>
void fooClass(py::module &m, const std::string &pythonName)
{
  py::class_<foo<T>>(m, pythonName.c_str(), py::module_local())
      .def(py::init<>())
      .def("clear", [](foo<T> &f)
           { f.items_.clear(); })
      .def("append", [](foo<T> &f, const T val)
           { f.items_.push_back(val); })
      .def("get_items", &foo<T>::getItems, py::return_value_policy::reference)
      .def("get_items_copy", &foo<T>::getItems, py::return_value_policy::copy)
      .def("empty", [](foo<T> const &f)
           { return f.items_.empty(); })
      .def("__len__", [](foo<T> const &f)
           { return f.items_.size(); })
      .def("__eq__", [](foo<T> const &f1, foo<T> const &f2)
           { 
            if(f1.getName() != f2.getName()) return false;
            if (f1.items_.size() != f2.items_.size()) return false;
            for(size_t i = 0; i < f1.items_.size(); ++i)
              if(f1.items_[i] != f2.items_[i])
                return false;
            return true; })
      .def("__getitem__", [](foo<T> const &f, size_t idx)
           { return f.items_[idx]; })
      .def("__setitem__", [](foo<T> &f, size_t idx, T val)
           { f.items_[idx] = val; });
}

template <typename T>
void vectorize(py::module &m, const std::string &pythonName)
{
  py::class_<std::vector<T>>(m, pythonName.c_str(), py::module_local())
      .def(py::init<>())
      .def(py::init<const std::vector<T> &>())
      .def(py::init([](const py::iterable &it) {
          auto v = std::unique_ptr<std::vector<T>>(new std::vector<T>());
          v->reserve(len_hint(it));
          for (const auto &h : it)
              v->push_back(h.cast<T>());
          return v.release();
        }))
      .def("clear", &std::vector<T>::clear)
      .def("pop_back", &std::vector<T>::pop_back)
      .def("append", [](std::vector<T> &v, const T val)
          { v.push_back(val); })
      .def("convert", [](std::vector<T> &v, const py::list &l)
          { 
            v.clear();
            for(const auto &item : l)
              v.push_back(item.cast<T>());
            return v;
          })
      .def("empty", &std::vector<T>::empty)
      .def("__len__", [](const std::vector<T> &v)
           { return v.size(); })
      .def("__eq__", [](const std::vector<T> &v1, const std::vector<T> &v2)
           { if (v1.size() != v2.size()) return false;
             for(size_t i = 0; i < v1.size(); ++i)
               if(v1[i] != v2[i])
                 return false;
             return true; })
      .def("__getitem__", [](const std::vector<T> &v, size_t idx)
           { return v[idx]; })
      .def("__setitem__", [](std::vector<T> &v, size_t idx, T val)
           {
             if (v.size() <= idx)
               v.resize(idx + 1);
             v[idx] = val;
           })
      .def(
          "__iter__", [](std::vector<T> &v)
          { return py::make_iterator(v.begin(), v.end()); },
          py::keep_alive<0, 1>());
  py::implicitly_convertible<py::list, std::vector<T>>();
}
