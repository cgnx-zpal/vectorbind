cmake_minimum_required(VERSION 3.21)

project(vectorbind LANGUAGES CXX VERSION 1.0)

set (PYBIND11_PYTHON_VERSION "3.10")
set(pybind11_DIR "/work/.local/lib/python3.10/site-packages/pybind11/share/cmake/pybind11")
find_package(pybind11 CONFIG REQUIRED)
set(tsl-robin-map_DIR "/home/cognoid/.conandata/robin_map/1.2.1+3-e84f756/cognex/master/package/57e1b5089aa7cc907cdda73801c398dfdf4aebaf/share/cmake/tsl-robin-map")
set(nanobind_DIR "/home/cognoid/.conandata/nanobind/1.4.0+7-7c47dd3/cognex/dev/package/db4690d5444566e9d0bfc5c358ac7af53fe217d4/lib/cmake/nanobind")
find_package(nanobind CONFIG REQUIRED)

pybind11_add_module(Vector_Opaq_Bind  Vector_Opaq_Bind.cpp Vector_Common_py.cpp)
nanobind_add_module(Vector_Nano_Bind  Vector_Nano_Bind.cpp Vector_Common_nb.cpp)
