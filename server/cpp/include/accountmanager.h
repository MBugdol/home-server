#ifndef HOSE_ACCOUNTMANAGER_H
#define HOSE_ACCOUNTMANAGER_H

#include <string>

namespace HomeServer
{

class AccountManager 
{
private:
	std::string m_password;
	std::string m_salt;
	std::string m_hash;
};

} // namespace HomeServer

#endif // HOSE_ACCOUNTMANAGER_H
