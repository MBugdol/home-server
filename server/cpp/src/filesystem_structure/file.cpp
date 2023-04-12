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

	//void File::create() const
	//{
	//	if (!isValid())
	//		throw std::invalid_argument{ "Can't create directory outside of server's root!" };
	//	throw; //unimplemented
	//}

} // namespace HomeServer