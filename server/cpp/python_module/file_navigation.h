#ifndef HOSE_PYTHON_FILE_NAVIGATION_H
#define HOSE_PYTHON_FILE_NAVIGATION_H

#include <string>

namespace HomeServer::Python
{

std::string list(const std::string& path);
std::string search(const std::string& path,
	const std::string& phrase);
std::string info(const std::string& path);

} // namespace HomeServer::Python

#endif // HOSE_PYTHON_FILE_NAVIGATION_H