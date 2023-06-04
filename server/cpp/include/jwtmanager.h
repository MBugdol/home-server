#ifndef HOSE_SESSION_MANAGER
#define HOSE_SESSION_MANAGER

#include <string>
#include <nlohmann/json.hpp>

#include <jwttable.h>

namespace HomeServer
{

class JWTManager
{
public:
	enum TokenStatus {
		Valid,
		Expired,
		Revoked
	};

	JWTManager(const std::string& jwt);
	TokenStatus checkSession();
private:
	void extractPartsFromJwt(const std::string& jwt);
private:
	JWTTable m_table;
	nlohmann::json m_header;
	nlohmann::json m_payload;
	std::string m_signature;
};

} // namespace HomeServer

#endif // HOSE_SESSION_MANAGER