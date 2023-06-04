#ifndef HOSE_ACCOUNTMANAGER_H
#define HOSE_ACCOUNTMANAGER_H

#include <string>
#include <stdexcept>

#include <user.h>
#include <userstable.h>

namespace HomeServer
{

class AuthenticationException : public std::runtime_error
{
public:
	enum ErrorCode {
		NoError = 0,
		Undefined,
		// 100 - login errors
		// 200 - registration errors
		UserAlreadyExists = 200
	};
	static constexpr const char* errorCodeToMessage(const ErrorCode e);
	AuthenticationException(const ErrorCode e);
private:
	ErrorCode m_err_code;
};

class AccountManager 
{
public:
	AccountManager();
	void registerUser(const std::string& username, const std::string& password_plain);
	bool checkCredentials(const std::string& username, const std::string& password_plain);
private:
	void loadUserFromDatabase(const std::string& username);
private:
	static const size_t pbkdf_iteration_count = 50'000;

	UsersTable m_users_table;
	User m_user;
};

} // namespace HomeServer

#endif // HOSE_ACCOUNTMANAGER_H
