#ifndef HOSE_DATABASE
#define HOSE_DATABASE

#include <unordered_map>
#include <string>

#include <sqlite3.h>
//#include "../vendor/sqlite/sqlite3.h"

namespace HomeServer 
{


/// 
/// \brief Responsible for database connections.
/// 
/// Creates and destroys database handlers/connections.
/// 
class Database
{
public:
	Database(const Database&) = delete;
	Database(Database&&) = delete;
	Database& operator=(const Database&) = delete;
	Database& operator=(const Database&&) = delete;

	static Database& instance();
	void open(const std::string& path, const std::string& as = "");
	void close(const std::string& connection_name);
	sqlite3* get(const std::string& connection_name);
private:
	Database();
	~Database();
	static Database m_instance;

	std::unordered_map<std::string, sqlite3*> m_handlers;
};

} // namespace HomeServer

#endif // HOSE_DATABASE