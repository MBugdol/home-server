#include <accountmanager.h>
#include <database.h>
#include <random>
#include <sstream>
#include <format>

namespace HomeServer
{

AccountManager::AccountManager()
	: m_users_table{Database::instance().get("testdb")}
{
}

void AccountManager::registerUser(const std::string& username, const std::string& password_plain)
{

}

std::string AccountManager::getRandom128BitString()
{
	std::random_device randdev;
	std::mt19937_64 engine{ randdev()};
	std::uniform_int_distribution<uint64_t> dist;
	std::string repr = std::format("{0:0>16x}{1:0>16x}", dist(engine), dist(engine));
	return repr;
}

} // namespace HomeServer