#include "file_transfer.h"

#include <file.h>
#include <uploadmanager.h>
#include <filemetadata.h>

namespace HomeServer::Python
{

namespace fs = std::filesystem;

std::string initilizeFileTransfer(const std::string& path,
	const std::string& filename,
	const uint64_t filesize,
	const std::string& metadata_json)
{
	// TODO: create UploadManager and FileMetadata classess
	// TODO: add this when PermissionManager will have been created
	//PermissionManager pm;
	//if(!pm.canWrite(path))
	//	throw InvalidCredentials("NoWritePermission");

	//// TODO: start here
	//File target_file{ std::filesystem::path{path} / filename };
	//if (target_file.exists())
	//	throw std::runtime_error("AlreadyExists");

	//UploadManager um{ target_file };
	//if (um.ongoingUpload())
	//	throw std::runtime_error("UploadInProgress");

	// TODO: next up
	//FileMetadata meta = FileMetadata::fromJson(metadata_json);
	//um.setMetadata(meta);
	//return um.startUpload();
	// or return um.getUploadId();
	return "0123456789abcdef";
}

void create(const std::string& path,
	const std::string& entry_name,
	const std::string& metadata_json)
{
	FileMetadata meta = FileMetadata::fromJson(metadata_json);
	Entry::EntryType entry_type;
	if (meta.mime_type == "application/x-directory")
		entry_type = Entry::EntryType::Folder;
	else
		entry_type = Entry::EntryType::File;

	std::unique_ptr<Entry> new_entry = Entry::createEntryFromPath( fs::path{path} / entry_name, entry_type);
	if (!new_entry->valid())
		throw std::runtime_error("InvalidPath");

	if (!new_entry->parentDirExists())
		throw std::runtime_error("InvalidPath");

	if (new_entry->exists())
		throw std::runtime_error("AlreadyExists");

	new_entry->create();
}

}