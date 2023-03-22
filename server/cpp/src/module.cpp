#include <pybind11/pybind11.h>

namespace py = pybind11;

int add(int i, int j) {
	return i + j;
}

PYBIND11_MODULE(backend, m) {
	m.doc() = "A test plugin";
	m.def("add", add, "Dodaje dwie liczby");
}