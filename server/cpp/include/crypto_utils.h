#ifndef HOSE_CRYPTO_UTILS
#define HOSE_CRYPTO_UTILS

#include <string>

#include <cryptopp/secblock.h>

namespace HomeServer::Utils
{
	
CryptoPP::SecByteBlock getRandomByteBlock(const size_t size);

std::string secByteBlockToHexString(const CryptoPP::SecByteBlock& bytes);
CryptoPP::SecByteBlock hexStringToSecByteBlock(const std::string& hex_string);

std::string encodeBase64(const std::string& decoded);
std::string decodeBase64(const std::string& encoded);
bool isBase64(const std::string& s);

CryptoPP::SecByteBlock stringToSecByteBlock(const std::string& string);

/// \brief Performs a cryptographicaly secure comparison of buffer contents
/// \param buf1 the first buffer
/// \param buf2 the second buffer
/// 
/// \detail The buffers must be the same size for the function to be cryptographically secure
/// \returns true if \p buf1 == \p buf2, otherwise returns false
bool secureCompare(CryptoPP::SecByteBlock buf1, CryptoPP::SecByteBlock buf2);

CryptoPP::SecByteBlock hashPbkdf2(const CryptoPP::SecByteBlock& password, const CryptoPP::SecByteBlock& salt, const size_t iteration_count);

} // namespace HomeServer::Utils

#endif // HOSE_CRYPTO_UTILS