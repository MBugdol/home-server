#ifndef HOSE_PYTHON_FILE_TRANSFER_H
#define HOSE_PYTHON_FILE_TRANSFER_H

#include <string>

namespace HomeServer::Python
{

std::string initilizeFileTransfer(const std::string& path,
	const std::string& filename,
	const uint64_t filesize,
	const std::string& metadata_json);

void create(const std::string& path,
	const std::string& entry_name,
	const std::string& metadata_json);

}

#endif // HOSE_PYTHON_FILE_TRANSFER_H