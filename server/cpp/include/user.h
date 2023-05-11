#ifndef HOSE_USER_H
#define HOSE_USER_H

#include <optional>
#include <string>

namespace HomeServer
{

struct User
{
	std::optional<int> id;
	std::string username;
	std::string password_hash;
	std::string salt;
};

} // namespace HomeServer
#endif // HOSE_USER_H