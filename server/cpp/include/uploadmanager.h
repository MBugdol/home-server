#ifndef HOSE_UPLOAD_MANAGER_H
#define HOSE_UPLOAD_MANAGER_H

#include <memory>
#include <optional>

#include <file.h>
#include <uploadtable.h>
#include <filemetadata.h>

namespace HomeServer
{

class UploadManager
{
public:
	UploadManager(const File& file);

	// returns upload id 
	uint64_t startUpload();
	bool uploadStarted();
	void setMetadata(const FileMetadata& meta);
private:
	std::unique_ptr<Entry> m_destination;
	std::optional<FileMetadata> m_metadata;
	UploadTable m_table;
};

} // namespace HomeServer

#endif // HOSE_UPLOAD_MANAGER_H