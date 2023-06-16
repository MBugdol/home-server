#include <pybind11/pybind11.h>

#include "python_module/file_transfer.h"

namespace py = pybind11;

namespace HosePy = HomeServer::Python;

PYBIND11_MODULE(backend, m) {
	m.doc() = "The HomeServer backend module";
	m.def("initializeFileTransfer", HosePy::initilizeFileTransfer);
	m.def("create", HosePy::create);
	m.def("upload", HosePy::upload);
}