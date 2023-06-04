#include <accountmanager.h>
#include <random>
#include <sstream>
#include <format>
#include <cassert>

#include <database.h>
#include <crypto_utils.h>
#include <debug.h>

namespace HomeServer
{

	AccountManager::AccountManager()
		: m_users_table{ Database::instance().get("hose") }
	{
	}

	void AccountManager::registerUser(const std::string& username, const std::string& password_plain)
	{
		using namespace CryptoPP;
		const size_t salt_size_bytes = 16;

		SecByteBlock password_crypto = Utils::stringToSecByteBlock(password_plain);
		SecByteBlock salt_crypto = Utils::getRandomByteBlock(salt_size_bytes);
		SecByteBlock password_hashed_crypto = Utils::hashPbkdf2(password_crypto, salt_crypto, AccountManager::pbkdf_iteration_count);

		std::string password_hashed_hex = Utils::secByteBlockToHexString(password_hashed_crypto);
		std::string salt_hex = Utils::secByteBlockToHexString(salt_crypto);

		m_user = {
			std::nullopt,
			username,
			password_hashed_hex,
			salt_hex
		};

		try
		{
			m_users_table.insertUser(m_user);
		}
		catch (const std::exception& e)
		{
			throw AuthenticationException(AuthenticationException::UserAlreadyExists);
		}
		m_user.id = m_users_table.getUserId(username);
	}

	void AccountManager::loadUserFromDatabase(const std::string& username)
	{
		m_user = m_users_table.getUserByUsername(username);
	}

	bool AccountManager::checkCredentials(const std::string& username, const std::string& password_plain)
	{
		loadUserFromDatabase(username);
		CryptoPP::SecByteBlock input_hash = Utils::hashPbkdf2(Utils::stringToSecByteBlock(password_plain), Utils::hexStringToSecByteBlock(m_user.salt), AccountManager::pbkdf_iteration_count);
		return Utils::secureCompare(Utils::hexStringToSecByteBlock(m_user.password_hash), input_hash);
	}

	constexpr const char* AuthenticationException::errorCodeToMessage(const ErrorCode e)
	{
		switch (e)
		{
		case NoError:
			return "No error";
		case UserAlreadyExists:
			return "The user already exists!";
		case Undefined:
		default:
			return "Undefined authentication error";
		}
	}
	AuthenticationException::AuthenticationException(const ErrorCode e)
		: std::runtime_error{ errorCodeToMessage(e) }, m_err_code{e}
{
}

} // namespace HomeServer