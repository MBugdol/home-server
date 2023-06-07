#include <filemetadata.h>

namespace HomeServer
{

FileMetadata FileMetadata::fromJson(const std::string& metadata_str)
{
	using json = nlohmann::json;
	json metadata = json::parse(metadata_str);
	return metadata.get<FileMetadata>();
}

void from_json(const nlohmann::json& j, FileMetadata& m)
{
	using json = nlohmann::json;
	j.at("type").get_to(m.mime_type);
}


} // namespace HomeServer

