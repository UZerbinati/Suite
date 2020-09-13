#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(suite, m) {
    m.attr("release") = "0.0.1";
}
