#ifndef HOSE_SESSIONS_TABLE
#define HOSE_SESSIONS_TABLE

#include <query.h>

namespace HomeServer
{

class JWTTable
{
public:
	JWTTable(sqlite3* database);
private:
	void initialize();
private:
	sqlite3* m_database;
	Query m_query;
};

} // namespace HomeServer

#endif // HOSE_SESSIONS_TABLE