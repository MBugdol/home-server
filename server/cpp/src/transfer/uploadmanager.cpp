#include <uploadmanager.h>
#include <database.h>

namespace HomeServer
{

UploadManager::UploadManager(const File& file)
	: m_destination(std::make_unique<File>(file)), m_table{ Database::instance().get("hose") }
{
}

uint64_t UploadManager::startUpload()
{
	m_table.insertUpload(m_destination->path().string());
	return m_table.getUploadId(m_destination->path().string());
}

bool UploadManager::ongoingUpload() const
{
	return true;
}


} // namespace HomeServer