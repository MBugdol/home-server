#include <userstable.h>
#include <debug.h>

namespace HomeServer
{

UsersTable::UsersTable()
	: m_database(Database::instance().get("testdb"))
{
	initialize();
}
void UsersTable::initialize()
{
	debug() << "Create users table if not exists";
	const char* query = "CREATE TABLE IF NOT EXISTS Users ("
		"UserId INTEGER PRIMARY KEY, "
		"Username TEXT NOT NULL, "
		"PasswordHash TEXT NOT NULL, "
		"Salt TEXT NOT NULL"
		")";
}

void UsersTable::insertUser(const std::string& username, 
	const std::string& hash, 
	const std::string& salt)
{
	const char* query = "INSERT INTO Users (Username, PasswordHash, Salt) "
		"VALUES (?, ?, ?)";
	sqlite3_stmt* stmt;
	sqlite3_prepare(m_database, query, strlen(query), &stmt, nullptr);
	sqlite3_bind_text(stmt, 1, username.c_str(), username.size(), nullptr);
	sqlite3_bind_text(stmt, 2, hash.c_str(), hash.size(), nullptr);
	sqlite3_bind_text(stmt, 3, salt.c_str(), salt.size(), nullptr);
	//if(sqlite3_step(stmt) != SQLITE_DONE)
	//	throw;
	sqlite3_finalize(stmt);

}


std::vector<User> UsersTable::getAllUsers()
{
	const char* query = "SELECT UserId, Username, PasswordHash, Salt "
		"FROM Users";
	sqlite3_stmt* stmt;
	sqlite3_prepare(m_database, query, strlen(query), &stmt, nullptr);

	std::vector<User> result;
	bool done = false;
	while (!done)
	{
		User u;
		switch (sqlite3_step(stmt))
		{
		case SQLITE_ROW:
			u.id = sqlite3_column_int(stmt, 0);
			u.username = (const char*) sqlite3_column_text(stmt, 1);
			u.password_hash = (const char*)sqlite3_column_text(stmt, 2);
			u.salt = (const char*)sqlite3_column_text(stmt, 3);
			result.push_back(u);
			break;
		case SQLITE_DONE:
			done = true;
			break;
		}
	}
	sqlite3_finalize(stmt);

	return result;
}

} // namespace HomeServer