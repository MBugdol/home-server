#ifndef HOSE_USERS_TABLE
#define HOSE_USERS_TABLE

#include <database.h>
#include <user.h>
#include <query.h>

namespace HomeServer
{

class UsersTable
{
public:
	UsersTable(sqlite3* database);
	std::vector<User> getAllUsers();
	void insertUser(const User& user);
	std::optional<int64_t> getUserId(const std::string username);
private:
	void initialize();
private:
	sqlite3* m_database;
	Query m_query;
};

} // namespace HomeServer

#endif // HOSE_USERS_TABLE