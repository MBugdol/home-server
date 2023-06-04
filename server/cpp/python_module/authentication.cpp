#include "authentication.h"

#include <accountmanager.h>

void registerUser(const std::string& username, const std::string& password)
{
	HomeServer::AccountManager accmgr;
	accmgr.registerUser(username, password);
}

bool login(const std::string& username, const std::string& password)
{
	HomeServer::AccountManager accmgr;
	return accmgr.checkCredentials(username, password);
}