#include <crypto_utils.h>

#include <cassert>
#include <algorithm>

#include <cryptopp/osrng.h> // OS_GenerateRandomBlock
#include <cryptopp/pwdbased.h> // hashing
#include <cryptopp/misc.h>
#include <cryptopp/hex.h>
#include <cryptopp/base64.h>


namespace HomeServer::Utils
{

CryptoPP::SecByteBlock getRandomByteBlock(const size_t size)
{
	using namespace CryptoPP;
	SecByteBlock rand{ size };
	OS_GenerateRandomBlock(false, rand, rand.size());
	return rand;
}

std::string secByteBlockToHexString(const CryptoPP::SecByteBlock& bytes)
{
	using namespace CryptoPP;
	std::string hex_string;
	StringSource ss(bytes.data(), bytes.size(), true, new HexEncoder(new StringSink(hex_string)));
	return hex_string;
}

CryptoPP::SecByteBlock hexStringToSecByteBlock(const std::string& hex_string)
{
	using namespace CryptoPP;
	assert(hex_string.length() % 2 == 0);
	std::string decoded_str;
	StringSource ss(hex_string, true, new HexDecoder(new StringSink(decoded_str)));
	return stringToSecByteBlock(decoded_str);
}


CryptoPP::SecByteBlock stringToSecByteBlock(const std::string& string)
{
	using namespace CryptoPP;
	SecByteBlock result{ reinterpret_cast<const byte*>(&string[0]), string.size() };
	return result;
}

// BASE 64

std::string encodeBase64(const std::string& decoded)
{
	using namespace CryptoPP;
	std::string encoded;
	StringSource ss(decoded, true, new Base64Encoder(new StringSink(encoded)));
	return encoded;
}

std::string decodeBase64(const std::string& encoded)
{
	using namespace CryptoPP;

	std::string decoded;
	StringSource ss(encoded, true, new Base64Decoder(new StringSink(decoded)));
	return decoded;
}

bool isBase64(const std::string& s)
{	
	auto res = std::find_if_not(s.begin(), s.end(), [](char ch) {return isalnum(ch) || ch == '/' || ch == '+' || ch == '='; });
	if (res == s.end())
		return true;
	return false;
}	
	
	
CryptoPP::SecByteBlock hashPbkdf2(const CryptoPP::SecByteBlock& password, const CryptoPP::SecByteBlock& salt, const size_t iteration_count)
{
	using namespace CryptoPP;
	SecByteBlock derived{SHA512::DIGESTSIZE};
	PKCS5_PBKDF2_HMAC<SHA512> pbkdf;
	const byte unused = 0;

	pbkdf.DeriveKey(derived, derived.size(), unused, password, password.size(), salt, salt.size(), iteration_count, unused);
	return derived;
}

bool secureCompare(CryptoPP::SecByteBlock buf1, CryptoPP::SecByteBlock buf2)
{
	if (buf1.size() != buf2.size())
		return false;
	return CryptoPP::VerifyBufsEqual(buf1, buf2, buf1.size());
}



} // namespace HomeServer::Utils