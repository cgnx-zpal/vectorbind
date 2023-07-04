#include "Vector_Common.hpp"

#include <nanobind/nanobind.h>
#include <nanobind/stl/bind_vector.h>

#include <vector>
#include <memory>

namespace nb = nanobind;

extern void bindBigData(nb::module_ &m, const std::string &name);

template <typename T>
void fooClass(nb::module_ &m, const std::string &name)
{
  nb::class_<foo<T>>(m, name.c_str()/*, nb::module_local()*/) // https://nanobind.readthedocs.io/en/latest/porting.html#removed-features
      .def(nb::init<>())
      .def("clear", [](foo<T> &f)
           { f.items_.clear(); })
      .def("append", [](foo<T> &f, const T val)
           { f.items_.push_back(val); })
      .def("get_items", &foo<T>::getItems, nb::rv_policy::reference)
      .def("get_items_copy", &foo<T>::getItems, nb::rv_policy::copy)
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
void vectorize(nb::module_ &m, const std::string &name)
{
  nb::class_<std::vector<T>>(m, name.c_str()/*, nb::module_local()*/) // https://nanobind.readthedocs.io/en/latest/porting.html#removed-features
      .def(nb::init<>())
      .def(nb::init<const std::vector<T> &>())
      .def(nb::init([](const nb::iterable &it) {
          auto v = std::unique_ptr<std::vector<T>>(new std::vector<T>());
          v->reserve(len_hint(it));
          for (const auto &h : it)
              v->push_back(nb::cast<T &>(h));
          return v.release();
        }))
      .def("clear", &std::vector<T>::clear)
      .def("pop_back", &std::vector<T>::pop_back)
      .def("append", [](std::vector<T> &v, const T val)
          { v.push_back(val); })
      .def("convert", [](std::vector<T> &v, const nb::list &l)
          { 
            v.clear();
            for(const auto &item : l)
              v.push_back(nb::cast<T &>(item));
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
          { return nb::make_iterator(v.begin(), v.end()); },
          nb::keep_alive<0, 1>());
  nb::implicitly_convertible<nb::list, std::vector<T>>();
}
