#ifndef HOSE_UPLOAD_MANAGER_H
#define HOSE_UPLOAD_MANAGER_H

#include <memory>

#include <file.h>
#include <uploadtable.h>

namespace HomeServer
{

class UploadManager
{
public:
	UploadManager(const File& file);

	// returns upload id 
	uint64_t startUpload();
	bool ongoingUpload() const;
private:
	std::unique_ptr<Entry> m_destination;
	UploadTable m_table;
};

} // namespace HomeServer

#endif // HOSE_UPLOAD_MANAGER_H