#include <userstable.h>

#include <ranges>

#include <debug.h>
#include <queryiterator.h>


namespace HomeServer
{

UsersTable::UsersTable(sqlite3* database)
	: m_database{database}, m_query{ database }
{
	initialize();
}
void UsersTable::initialize()
{
	debug() << "Create users table if not exists";
	std::string query = "CREATE TABLE IF NOT EXISTS Users (\n"
		"\tUserId INTEGER PRIMARY KEY,\n"
		"\tUsername TEXT NOT NULL UNIQUE,\n"
		"\tPasswordHash TEXT NOT NULL,\n"
		"\tSalt TEXT NOT NULL\n"
		")";
	m_query.execute(query);
}

std::optional<int64_t> UsersTable::getUserId(const std::string username)
{
	std::string query = "SELECT UserId FROM Users "
		"WHERE Username = ?";
	m_query.prepare(query);
	m_query.bind(1, username);
	m_query.execute();
	int64_t id = std::get<0>(*QueryIterator<int64_t>{ m_query }.begin());
	return id;
}

void UsersTable::insertUser(const User& user)
{
	std::string query = "INSERT INTO Users ("
		"UserId, Username, PasswordHash, Salt"
		") VALUES ("
		"?, ?, ?, ?"
		")";
	m_query.prepare(query);
	m_query.bind_nullable(1, user.id);
	m_query.bind(2, user.username);
	m_query.bind(3, user.password_hash);
	m_query.bind(4, user.salt);
	m_query.execute();
}

User UsersTable::getUserByUsername(const std::string& username)
{
	std::string query = "SELECT UserId, PasswordHash, Salt "
		"FROM Users "
		"WHERE Username = ?";
	m_query.prepare(query);
	m_query.bind(1, username);
	m_query.execute();

	auto [id, password_hashed, salt] = *QueryIterator<uint64_t, std::string, std::string>{ m_query }.begin();
	return {
		id,
		username,
		password_hashed,
		salt
	};
}

User UsersTable::getUserById(const int64_t id)
{
	std::string query = "SELECT Username, PasswordHash, Salt "
		"FROM Users "
		"WHERE UserId = ?";
	m_query.bind(1, id);

	auto [username, password_hashed, salt] = *QueryIterator<std::string, std::string, std::string>{ m_query }.begin();
	return {
		id,
		username,
		password_hashed,
		salt
	};
}

std::vector<User> UsersTable::getAllUsers()
{
	std::string query = "SELECT UserId, Username, PasswordHash, Salt "
		"FROM Users";

	m_query.execute(query);

	std::vector<User> result{};
	for (auto [userid, name, hash, salt] : QueryIterator<size_t, std::string, std::string, std::string>{ m_query })
	{
		result.emplace_back(userid, name, hash, salt);
	}

	return result;
}

} // namespace HomeServer