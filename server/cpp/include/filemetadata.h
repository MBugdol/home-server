#ifndef HOSE_FILE_METADATA_H
#define HOSE_FILE_METADATA_H

#include <string>
#include <nlohmann/json.hpp>

namespace HomeServer
{

struct FileMetadata
{
	std::string mime_type;
	
	static FileMetadata fromJson(const std::string& metadata_str);
};

void from_json(const nlohmann::json& j, FileMetadata& m);


} // namespace HomeServer

#endif // HOSE_FILE_METADATA_H