#include <uploadmanager.h>
#include <database.h>
#include <debug.h>

namespace HomeServer
{

UploadManager::UploadManager(const File& file)
	: m_destination(std::make_unique<File>(file)), m_table{ Database::instance().get("hose") }
{
}

uint64_t UploadManager::startUpload()
{
	// TODO:
	m_table.insertUpload(m_destination->path().string());
	m_destination->create();
	return m_table.getUploadId(m_destination->path().string());
}

bool UploadManager::uploadStarted()
{
	return m_table.uploadExists(m_destination->path().string());
}

void UploadManager::setMetadata(const FileMetadata& meta)
{
	m_metadata = meta;
}


} // namespace HomeServer