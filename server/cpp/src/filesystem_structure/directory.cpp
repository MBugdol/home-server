#include "directory.h"
#include <ranges>
#include "debug.h"

namespace HomeServer
{

namespace fs = std::filesystem;
namespace ranges = std::ranges;

Directory::Directory(const fs::path& path)
	: Entry(path)
{
	debug();
}

void Directory::create() const
{
	if (!isValid())
		throw std::invalid_argument{ "Can't create directory outside of server's root!" };
	if (fs::exists(fullPath()))
		throw std::runtime_error{ "The given directory already exists!" };
	try
	{
		fs::create_directory(fullPath());
	}
	catch (const std::exception& e)
	{
		debug() << "Failed to create a directory under" << fullPath().string();
		debug() << "Reason:" << e.what();
		throw;
	}
}
std::string Directory::json() const
{
	std::string str = "{";
	str += R"("type"=directory,)";
	str += R"("name"=)" + m_path.filename().string();
	str += R"("children"=[])";
	str += "}";
	return str;
}

std::vector<std::unique_ptr<Entry>> Directory::children() const
{
	std::vector<std::unique_ptr<Entry>> result;
	//ranges::copy(fs::directory_iterator(fullPath()) | ranges::views::transform(), std::back_inserter(result));
	return {};
}

} // namespace HomeServer