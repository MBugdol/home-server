#ifndef HOSE_ACCOUNTMANAGER_H
#define HOSE_ACCOUNTMANAGER_H

#include <string>
#include <user.h>
#include <userstable.h>

namespace HomeServer
{

class AccountManager 
{
public:
	AccountManager();
	void registerUser(const std::string& username, const std::string& password_plain);
//private:
	std::string getRandom128BitString();
private:
	UsersTable m_users_table;
	User m_user;
};

} // namespace HomeServer

#endif // HOSE_ACCOUNTMANAGER_H
