#include <jwttable.h>
#include <debug.h>

namespace HomeServer
{

JWTTable::JWTTable(sqlite3* database)
	: m_database(database), m_query(database)
{
	initialize();
}

void JWTTable::initialize()
{
	debug() << "Creating Sessions table if not exists";
	std::string query_string = "CREATE TABLE IF NOT EXISTS Tokens (\n"
		"\ttokenId INTEGER PRIMARY KEY,\n"
		"\tuserId INTEGER NOT NULL,\n"
		"\tjwt BLOB NOT NULL,\n"
		"\tsecret BLOB NOT NULL,\n"
		"\tFOREIGN KEY(userId) REFERENCES Users(userId)\n"
		"\tON UPDATE CASCADE\n"
		"\tON DELETE CASCADE\n"
		")";
}

} // namespace HomeServer