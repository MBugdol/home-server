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
		"\tuploadPath TEXT NOT NULL UNIQUE\n"
		")";
	m_query.execute(query_string);
}

void UploadTable::insertUpload(const std::string& target)
{
	std::string query_string = "INSERT INTO Uploads (uploadPath)"
		"VALUES (?)";
	m_query.prepare(query_string);
	m_query.bind(1, target);
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
	// TODO: is this used?
	std::string query_string = "SELECT uploadId FROM Uploads "
		"WHERE uploadPath = ?";
	m_query.prepare(query_string);
	m_query.bind(1, target);
	m_query.execute();
	return std::get<0>(*QueryIterator<int>{m_query}.begin());
}



} // namespace HomeServer