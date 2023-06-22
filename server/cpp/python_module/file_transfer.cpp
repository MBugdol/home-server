#include "file_transfer.h"

#include <file.h>
#include <uploadmanager.h>
#include <filemetadata.h>
#include <debug.h>

namespace HomeServer::Python
{

namespace fs = std::filesystem;

uint64_t initilizeFileTransfer(const std::string& path,
	const std::string& filename,
	const uint64_t filesize,
	const std::string& metadata_json)
{
	// TODO: add this when PermissionManager will have been created
	//PermissionManager pm;
	//if(!pm.canWrite(path))
	//	throw InvalidCredentials("NoWritePermission");

	using namespace EntryError;
	File target_file{ std::filesystem::path{path} / filename };
	if (target_file.exists())
		throw std::runtime_error(toString(AlreadyExists));

	UploadManager um{ target_file };
	if (um.uploadStarted())
		throw std::runtime_error("UploadInProgress");

	FileMetadata meta = FileMetadata::fromJson(metadata_json);
	um.setMetadata(meta);
	um.setSize(filesize);
	return um.startUpload();
}

void upload(const uint64_t upload_id,
	uint64_t start_byte,
	uint64_t end_byte,
	const std::string& data)
{
	// create UM with the upload_id
	UploadManager um = UploadManager::fromId(upload_id);

	// TODO: add this when PermissionManager will have been created
	//PermissionManager pm;
	//if(!pm.canWrite(path))
	//	throw InvalidCredentials("NoPermission");

	if (!um.uploadStarted())
		throw std::runtime_error("NoUpload");

	// check if bytes are correct
	File target = um.file();

	if (start_byte != target.size() ||
		end_byte > um.filesize() - 1)
		throw std::runtime_error("InvalidRange");

	uint64_t range_size = end_byte - start_byte + 1;
	if (range_size != data.size())
		throw std::runtime_error("SizeMismatch");

	target.append(data);
	if (target.size() == um.filesize())
		um.completeUpload();
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

void remove(const std::string& path)
{
	// TODO: add this when PermissionManager will have been created
	//PermissionManager pm;
	//if(!pm.canWrite(path))
	//	throw InvalidCredentials("NoWritePermission");

	if (!Entry::exists(path))
		throw std::runtime_error(EntryError::toString(EntryError::NonExistent));

	Entry::EntryType type = Entry::type(path);
	std::unique_ptr<Entry> entry = Entry::createEntryFromPath(path, type);
	entry->remove();
}


}