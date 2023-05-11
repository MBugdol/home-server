#include <database.h>
#include <debug.h>
#include <filesystem>

namespace HomeServer
{
	namespace fs = std::filesystem;

Database Database::m_instance;
Database::Database()
	: m_handlers{}
{
	debug() << "Opening necessary database connections...";
	fs::path test_db_location = fs::current_path() / "testdb.db";
	open(test_db_location.string(), "testdb");
	debug() << "Database singleton constructed";
}

Database::~Database()
{
	//RAII
	debug() << "Closing up the database...";
	for (auto it = m_handlers.begin(); it != m_handlers.end();)
	{
		try {
			close((it++)->first);
		}
		catch (const std::exception& e)
		{
			debug() << e.what();
			continue;
		}
	}
}

Database& Database::instance()
{
	return m_instance;
}

void Database::open(const std::string& path, const std::string& as)
{
	debug() << "Trying to estabilish database connection with" << path << "as" << as;
	sqlite3* handler = nullptr;
	int error;
	error = sqlite3_open(path.c_str(), &handler);
	
	if (error)
		throw std::runtime_error{ "Couldn't estabilish database connection with " + path + 
		", " + sqlite3_errmsg(handler) };

	std::string handler_name = as.empty() ? path : as;
	m_handlers.insert({handler_name, handler});
	debug() << "Successfuly estabilished connection!";
}

void Database::close(const std::string& connection_name)
{
	debug() << "Trying to close" << connection_name;
	sqlite3* handler = m_handlers[connection_name];
	int error = sqlite3_close(handler);
	if (error)
		throw std::runtime_error{"Failed to close database connection with " + connection_name + 
		", " + sqlite3_errmsg(handler)};
	m_handlers.erase(connection_name);
	debug() << "Successfuly closed" << connection_name;
}

sqlite3* Database::get(const std::string& connection_name)
{
	debug() << "Getting connection" << connection_name;
	try {
		sqlite3* handler = m_handlers.at(connection_name);
		return handler;
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error{ "Specified connection doesn't exist! Connection name: " + connection_name };
	}
}

} // namespace HomeServer