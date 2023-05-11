#ifndef HOSE_USERS_TABLE
#define HOSE_USERS_TABLE

#include <database.h>
#include <user.h>

namespace HomeServer
{

class UsersTable
{
public:
	UsersTable();
	std::vector<User> getAllUsers();
	void insertUser(const std::string& username, const std::string& hash, const std::string& salt);
private:
	void initialize();
private:
	sqlite3* m_database;
};

} // namespace HomeServer

#endif // HOSE_USERS_TABLE