#include "file.h"
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
		if (!valid())
			throw std::invalid_argument{ "InvalidPath" };
		throw; //unimplemented
	}

} // namespace HomeServer