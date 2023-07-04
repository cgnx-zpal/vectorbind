# vectorbind
compare the performance of nanobind and pybind11

to build:
```bash
cmake -S . -B buildr -D CMAKE_BUILD_TYPE=Release
cmake --build buildr
```
to execute:
`pytest -rP test_performance.py`
----
one possible result where the first value belongs to pybind11 and the second is to nanobind:
```text
Returns by reference:
  0.43122770002810284
  1.2800408999901265
Returns by value:
  1.0729455000255257
  1.9072670000023209
```
