#include "file.h"

#include <fstream>

#include "debug.h"

namespace HomeServer
{

	namespace fs = std::filesystem;

	File::File(const fs::path& path)
		: Entry(path)
	{
		debug();
	}

	void File::create() const
	{
		using namespace HomeServer::EntryError;
		if (!valid())
			throw std::invalid_argument{ toString(InvalidPath) };
		if (!parentDirExists())
			throw std::invalid_argument{ toString(NoParent) };
		if (exists())
			throw std::runtime_error{ toString(AlreadyExists) };

		std::ofstream file(fullPath());
		if (!file.is_open())
			throw std::runtime_error{ "InvalidName" };
	}

} // namespace HomeServer