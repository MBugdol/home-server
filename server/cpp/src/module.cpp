#include <pybind11/pybind11.h>
#include "file_access.h"

namespace py = pybind11;

using HomeServer::FileHandler;

PYBIND11_MODULE(backend, m) {
	m.doc() = "The HomeServer backend plugin";
	py::class_<FileHandler>(m, "FileHandler")
		.def(py::init<>())
		.def("createHomeServerDirectory", &FileHandler::createHomeServerDirectory)
		.def("createFolder", &FileHandler::createFolder);
}