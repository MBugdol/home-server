#ifndef HOSE_PYTHON_AUTHENTICATION
#define HOSE_PYTHON_AUTHENTICATION

#include <string>

void registerUser(const std::string& username, const std::string& password);
bool login(const std::string& username, const std::string& password);

#endif // HOSE_PYTHON_AUTHENTICATION