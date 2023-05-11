#include <query.h>
#include <debug.h>

namespace HomeServer
{

Query::Query(sqlite3* database)
	: m_db(database), m_stmt(nullptr)
{
}

Query::~Query()
{
	sqlite3_finalize(m_stmt);
}

void Query::prepare(const std::string& query_string)
{
	sqlite3_finalize(m_stmt); // in case somebody tries to reprepare a query
	//vvv perchance use last arg to display appropriate error message? (get the executed query)
	int err = sqlite3_prepare_v2(m_db, query_string.c_str(), query_string.length(), &m_stmt, nullptr);
	if (err)
		throw std::runtime_error(std::string{"Failed to prepare query! "} + sqlite3_errmsg(m_db));
}

void Query::execute()
{
	int err = sqlite3_step(m_stmt);
	if (err == SQLITE_DONE)
	{
		sqlite3_finalize(m_stmt);
		m_stmt = nullptr;
	}
}

void Query::execute(const std::string& query_string)
{
	prepare(query_string);
	execute();
}

void Query::bind(const int pos, const int val)
{
	int err = sqlite3_bind_int(m_stmt, pos, val);
	if (err)
		throw std::runtime_error{ std::string{"Failed to bind parameter to statement! "} + sqlite3_errmsg(m_db)};
}
void Query::bind(const int pos, const long long val)
{
	int err = sqlite3_bind_int64(m_stmt, pos, val);
	if (err)
		throw std::runtime_error{ std::string{"Failed to bind parameter to statement! "} + sqlite3_errmsg(m_db) };
}
void Query::bind(const int pos, const double val)
{
	int err = sqlite3_bind_double(m_stmt, pos, val);
	if (err)
		throw std::runtime_error{ std::string{"Failed to bind parameter to statement! "} + sqlite3_errmsg(m_db) };
}
void Query::bind(const int pos, const std::string& val)
{
	int err = sqlite3_bind_text(m_stmt, pos, val.c_str(), val.size(), SQLITE_STATIC);
	if (err)
		throw std::runtime_error{ std::string{"Failed to bind parameter to statement! "} + sqlite3_errmsg(m_db) };
}
void Query::bind(const int pos, const std::string&& val)
{
	int err = sqlite3_bind_text(m_stmt, pos, val.c_str(), val.size(), SQLITE_TRANSIENT);
	if (err)
		throw std::runtime_error{ std::string{"Failed to bind parameter to statement! "} + sqlite3_errmsg(m_db) };
}

} // namespace HomeServer