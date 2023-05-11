#include <pybind11/pybind11.h>
#include <file_access.h>

namespace py = pybind11;

namespace Hose = HomeServer;
using Hose::FileHandler;

PYBIND11_MODULE(backend, m) {
	m.doc() = "The HomeServer backend module";
	py::class_<FileHandler>(m, "FileHandler")
		.def(py::init<>())
		.def("createFolder", &FileHandler::createFolder);
}