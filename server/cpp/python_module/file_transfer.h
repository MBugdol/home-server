#ifndef HOSE_PYTHON_FILE_TRANSFER_H
#define HOSE_PYTHON_FILE_TRANSFER_H

#include <string>

namespace HomeServer::Python
{

uint64_t initilizeFileTransfer(const std::string& path,
	const std::string& filename,
	const uint64_t filesize,
	const std::string& metadata_json);

void create(const std::string& path,
	const std::string& entry_name,
	const std::string& metadata_json);

void upload(const uint64_t upload_id,
	uint64_t start_byte,
	uint64_t end_byte,
	const std::string& data);

}

#endif // HOSE_PYTHON_FILE_TRANSFER_H