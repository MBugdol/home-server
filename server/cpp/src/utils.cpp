#include <utils.h>

namespace HomeServer::Utils
{

std::vector<std::string> split(const std::string& str, char delim)
{
	std::vector<std::string> result;
	std::size_t after_prev_delim = 0;
	std::size_t delim_pos = str.find(delim);

	while (delim_pos != std::string::npos)
	{
		result.emplace_back(str.begin() + after_prev_delim, str.begin()+delim_pos);
		after_prev_delim = delim_pos + 1;
		delim_pos = str.find(delim, after_prev_delim);
	}
	result.emplace_back(str.begin() + after_prev_delim, str.end());

	return result;
}


} // namespace HomeServer::Utils