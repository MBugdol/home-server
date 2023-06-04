#include <jwtmanager.h>

#include <stdexcept>
#include <chrono>

#include <utils.h>
#include <crypto_utils.h>

namespace HomeServer
{

using json = nlohmann::json;
	
JWTManager::JWTManager(const std::string& jwt)
{
	extractPartsFromJwt(jwt);
}

JWTManager::TokenStatus JWTManager::checkSession()
{
	using namespace std::chrono;
	// check for the jwt in the database
	std::time_t current_time = system_clock::to_time_t(system_clock::now());
}

void JWTManager::extractPartsFromJwt(const std::string& jwt)
{
	using namespace HomeServer::Utils;
	auto parts = split(jwt, '.');
	if (parts.size() != 3)
		throw std::invalid_argument{"Supplied token isn't split into 3 parts!"};

	// validate parts
	if(!isBase64(parts[0]) || !isBase64(parts[1]))
		throw std::invalid_argument("Specified jwt is not base64 encoded!");

	m_header = json::parse(decodeBase64(parts[0]));
	m_payload = json::parse(decodeBase64(parts[1]));
	m_signature = parts[2];
}

} // namespace HomeServer