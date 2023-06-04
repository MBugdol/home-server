#include <debug.h>

#include <jwtmanager.h>

int main(int argc, char** argv)
{
	using namespace HomeServer;
	try {
		JWTManager jwt("eyJhbGciOiJIUzUxMiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiYWRtaW4iOnRydWUsImlhdCI6MTUxNjIzOTAyMn0.VFb0qJ1LRg_4ujbZoRMXnVkUgiuKq5KxWqNdbKq_G9Vvz-S1zZa9LPxtHWKa64zDl2ofkT8F6jBt_K4riU-fPg");
	}
	catch (const std::exception& e)
	{
		debug() << "Exception occured!";
		debug() << e.what();
		return 1;
	}
	return 0;
	
}