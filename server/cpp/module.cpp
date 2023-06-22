#include <pybind11/pybind11.h>

#include "python_module/file_transfer.h"
#include "python_module/file_navigation.h"

namespace py = pybind11;

namespace HosePy = HomeServer::Python;

PYBIND11_MODULE(backend, m) {
	m.doc() = "The HomeServer backend module";
	m.def("info", HosePy::info);
	m.def("list", HosePy::list);
	m.def("search", HosePy::search);
	m.def("create", HosePy::create);
	m.def("rename", HosePy::rename);
	m.def("move", HosePy::move);
	m.def("remove", HosePy::remove);
	m.def("initializeFileTransfer", HosePy::initilizeFileTransfer);
	m.def("upload", HosePy::upload);
	m.def("read", HosePy::read, py::arg("path"), py::arg("start"), py::arg("end") = uint64_t(-1));
}