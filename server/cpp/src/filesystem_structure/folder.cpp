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
	using namespace HomeServer::EntryError;
	if (!valid())
		throw std::invalid_argument{ toString(InvalidPath) };
	if (!parentDirExists())
		throw std::invalid_argument{ toString(NoParent) };
	if (exists())
		throw std::runtime_error{ toString(AlreadyExists) };

	fs::create_directory(fullPath());
}

} // namespace HomeServer