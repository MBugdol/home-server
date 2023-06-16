#include <uploadmanager.h>
#include <database.h>
#include <debug.h>

namespace HomeServer
{

UploadManager::UploadManager(const File& file)
	: m_destination(std::make_unique<File>(file)), m_table{ Database::instance().get("hose") }
{
}

UploadManager UploadManager::fromId(const uint64_t upload_id)
{
	UploadTable ut{ Database::instance().get("hose") };
	std::string target;
	try {
		target = ut.getUploadTarget(upload_id);
		return UploadManager{ File{target} };
	}
	catch (const std::exception e) {
		throw std::runtime_error{ "NoUpload" };
	}
}


uint64_t UploadManager::startUpload()
{
	m_table.insertUpload(m_destination->path().string(), m_size);
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

void UploadManager::setSize(const uint64_t size)
{
	m_size = size;
}

uint64_t UploadManager::currentByte()
{
	return m_table.getCurrentByte(m_destination->path().string());
}

uint64_t UploadManager::filesize()
{
	return m_table.getUploadSize(m_destination->path().string());
}

File& UploadManager::file()
{
	return *static_cast<File*>(m_destination.get());
}

void UploadManager::completeUpload()
{
	if (!uploadStarted())
		throw std::runtime_error("NoUpload");
	m_table.removeUpload(m_destination->path().string());
}

} // namespace HomeServer