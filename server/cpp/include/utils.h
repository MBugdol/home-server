#ifndef HOSE_UTILS_H
#define HOSE_UTILS_H

#include <vector>
#include <string>

namespace HomeServer::Utils
{

[[nodiscard]] std::vector<std::string> split(const std::string& str, char delim);

} // namespace HomeServer::Utils

#endif // HOSE_UTILS_H