#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
#include "./LA.hpp"
#include "./Calc.hpp"
#include "./Geo.hpp"
#include "./Discrete.hpp"
#include "../Parallel/Test.cpp"


//namespace py = pybind11;

PYBIND11_MODULE(suite, module) {
    module.attr("release") = "0.0.1";
    module.def("ParallelTest", []() {
      /* Release GIL before calling into C++ code */
      py::gil_scoped_release release;
      ParallelTest();
    });
    module.def("parallel_calc_pi", [](int n) {
      /* Release GIL before calling into C++ code */
      py::gil_scoped_release release;
      return parallel_calc_pi(n);
    });
    module.def("calc_pi", [](int n) {
      return calc_pi(n);
    });
    LABind(module);    
    CalcBind(module);
    GeoBind(module);
    DiscreteBind(module);
}
