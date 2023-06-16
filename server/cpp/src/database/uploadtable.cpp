#include <uploadtable.h>
#include <queryiterator.h>

namespace HomeServer
{

UploadTable::UploadTable(sqlite3* database)
	: m_database(database), m_query(database)
{
	initialize();
}



void UploadTable::initialize()
{
	std::string query_string = "CREATE TABLE IF NOT EXISTS Uploads (\n"
		"\tuploadId INTEGER PRIMARY KEY AUTOINCREMENT,\n"
		"\tuploadPath TEXT NOT NULL UNIQUE,\n"
		"\tuploadSize INTEGER NOT NULL,\n"
		"\tcurrentUploadByte INTEGER DEFAULT 0\n"
		")";
	m_query.execute(query_string);
}

void UploadTable::insertUpload(const std::string& target, const int upload_size)
{
	std::string query_string = "INSERT INTO Uploads (uploadPath, uploadSize) "
		"VALUES (?, ?)";
	m_query.prepare(query_string);
	m_query.bind(1, target);
	m_query.bind(2, upload_size);
	m_query.execute();
}

bool UploadTable::uploadExists(const std::string& target)
{
	std::string query_string = "SELECT COUNT(*) FROM Uploads "
		"WHERE uploadPath = ?";
	m_query.prepare(query_string);
	m_query.bind(1, target);
	m_query.execute();
	return static_cast<bool>(std::get<0>(*QueryIterator<int>{m_query}.begin()));
}

int UploadTable::getUploadId(const std::string& target)
{
	std::string query_string = "SELECT uploadId FROM Uploads "
		"WHERE uploadPath = ?";
	m_query.prepare(query_string);
	m_query.bind(1, target);
	m_query.execute();
	return std::get<0>(*QueryIterator<int>{m_query}.begin());
}

std::string UploadTable::getUploadTarget(const int upload_id)
{
	std::string query_string = "SELECT uploadPath FROM Uploads "
		"WHERE uploadId = ?";
	m_query.prepare(query_string);
	m_query.bind(1, upload_id);
	m_query.execute();
	return std::get<0>(*QueryIterator<std::string>{m_query}.begin());
}

int UploadTable::getCurrentByte(const std::string& target)
{
	std::string query_string = "SELECT currentUploadByte FROM Uploads "
		"WHERE uploadPath = ?";
	m_query.prepare(query_string);
	m_query.bind(1, target);
	m_query.execute();
	return std::get<0>(*QueryIterator<int>{m_query}.begin());
}

void UploadTable::setCurrentByte(const std::string& target, const int newbyte)
{
	std::string query_string = "UPDATE Uploads SET currentUploadByte = ? "
		"WHERE uploadPath = ?";
	m_query.prepare(query_string);
	m_query.bind(1, newbyte);
	m_query.bind(2, target);
	m_query.execute();

}

int UploadTable::getUploadSize(const std::string& target)
{
	std::string query_string = "SELECT uploadSize FROM Uploads "
		"WHERE uploadPath = ?";
	m_query.prepare(query_string);
	m_query.bind(1, target);
	m_query.execute();
	return std::get<0>(*QueryIterator<int>{m_query}.begin());
}

void UploadTable::removeUpload(const std::string& target)
{
	std::string query_string = "DELETE FROM Uploads "
		"WHERE uploadPath = ?";
	m_query.prepare(query_string);
	m_query.bind(1, target);
	m_query.execute();
}

} // namespace HomeServer