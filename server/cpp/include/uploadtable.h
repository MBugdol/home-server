#ifndef HOSE_UPLOAD_TABLE_H
#define HOSE_UPLOAD_TABLE_H

#include <query.h>

namespace HomeServer
{

class UploadTable
{
public:
	UploadTable(sqlite3* database);
	void initialize();

	// target - path to uploaded file
	void insertUpload(const std::string& target, const int upload_size);

	int getUploadId(const std::string& target);
	std::string getUploadTarget(const int upload_id);
	bool uploadExists(const std::string& target);

	int getCurrentByte(const std::string& target);
	int getUploadSize(const std::string& target);

	void setCurrentByte(const std::string& target, const int newbyte);

	void removeUpload(const std::string& target);
private:
	sqlite3* m_database;
	Query m_query;
};

} // namespace HomeServer

#endif // HOSE_UPLOAD_TABLE_H