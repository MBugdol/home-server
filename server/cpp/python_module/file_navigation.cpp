#include "file_navigation.h"

#include <nlohmann/json.hpp>

#include <folder.h>

namespace HomeServer::Python
{

std::string list(const std::string& path)
{
	Folder working_dir{ path };

	if (!working_dir.valid())
		throw std::runtime_error{ EntryError::toString(EntryError::InvalidPath) };

	// TODO: add this when PermissionManager will have been created
	//PermissionManager pm;
	//if(!pm.canRead(path))
	//	throw InvalidCredentials("NoReadPermission");

	if (!working_dir.exists())
		throw std::runtime_error{ EntryError::toString(EntryError::NonExistent) };

	return working_dir.jsonWithChildren().dump();
}

} // namespace HomeServer::Python