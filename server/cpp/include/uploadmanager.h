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
	static UploadManager fromId(const uint64_t upload_id);

	// returns upload id 
	uint64_t startUpload();
	bool uploadStarted();
	void setMetadata(const FileMetadata& meta);
	uint64_t currentByte();
	uint64_t filesize();

	void completeUpload();

	File& file();

	void setSize(const uint64_t size);
private:
	std::unique_ptr<Entry> m_destination;
	std::optional<FileMetadata> m_metadata;
	uint64_t m_size = 0;
	UploadTable m_table;
};

} // namespace HomeServer

#endif // HOSE_UPLOAD_MANAGER_H