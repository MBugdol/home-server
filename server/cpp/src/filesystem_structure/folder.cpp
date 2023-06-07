#include <folder.h>
#include <debug.h>

namespace HomeServer
{

namespace fs = std::filesystem;
namespace ranges = std::ranges;

Folder::Folder(const fs::path& path)
	: Entry(path)
{
	debug();
}

void Folder::create() const
{
	if (!valid())
		throw std::invalid_argument{ "InvalidPath" };
	if (!parentDirExists())
		throw std::invalid_argument{ "InvalidPath" };
	if (exists())
		throw std::runtime_error{ "AlreadyExists" };

	fs::create_directory(fullPath());
}

} // namespace HomeServer