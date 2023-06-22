#ifndef HOSE_PYTHON_FILE_TRANSFER_H
#define HOSE_PYTHON_FILE_TRANSFER_H

#include <string>
#include <pybind11/pybind11.h>

namespace HomeServer::Python
{

void create(const std::string& path,
	const std::string& entry_name,
	const std::string& metadata_json);

void rename(const std::string& path,
	const std::string& new_name);

void move(const std::string& path,
	const std::string& target);

void remove(const std::string& path);

uint64_t initilizeFileTransfer(const std::string& path,
	const std::string& filename,
	const uint64_t filesize,
	const std::string& metadata_json);

void upload(const uint64_t upload_id,
	uint64_t start_byte,
	uint64_t end_byte,
	const std::string& data);

pybind11::bytes read(const std::string& path,
	const uint64_t start,
	const uint64_t end = -1);

}

#endif // HOSE_PYTHON_FILE_TRANSFER_H