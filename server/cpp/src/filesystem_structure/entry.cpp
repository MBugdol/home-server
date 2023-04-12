#include <ranges>

#include "entry.h"
#include "directory.h"
#include "debug.h"

namespace HomeServer
{
namespace fs = std::filesystem;

//===\
// STATIC MEMBERS
//===/

const fs::path getServerRoot()
{
#ifdef HOSE_INSTALL_PATH
	fs::path server_root_path = fs::path{ HOSE_INSTALL_PATH };
#else
	fs::path server_root_path = fs::current_path().root_path() / "HomeServer";
#endif

	server_root_path.make_preferred();
	server_root_path = fs::weakly_canonical(server_root_path);
	debug() << "Server root path:" << server_root_path;

	//TODO: MOVE ASAP
	if (!fs::exists(server_root_path)) 
		fs::create_directories(server_root_path);

	return server_root_path;
}
const fs::path Entry::m_server_root_path = getServerRoot();

//===\
// STATIC MEMBER FUNCTIONS
//===/
Entry::EntryUniquePtr Entry::createEntryFromPath(const std::filesystem::path& path)
{
	return nullptr;
}

bool Entry::isValid(const std::filesystem::path& path)
{
	throw;
	return false;
}

fs::path Entry::serverRootPath()
{
	return m_server_root_path;
}

//===\
// CONSTRUCTORS
//===/
Entry::Entry()
	: m_path()
{
	debug();
}

Entry::Entry(const std::filesystem::path& path)
	: m_path(path)
{
	debug();
}

//===\
// PUBLIC MEMBER FUNCTIONS
//===/

// getters

fs::path Entry::path() const
{
	return m_path;
}

// properties

bool Entry::isValid() const
{
	return isContainedInServerRoot();
}

//==\
// PRIVATE MEMBER FUNCTIONS
//==/

// utilities

fs::path Entry::fullPathNoValidation() const noexcept
{
	return fs::weakly_canonical(m_server_root_path / m_path);
}

fs::path Entry::fullPath() const
{
	return fullPathNoValidation();
}

// properties

bool Entry::isContainedInServerRoot() const
{
	namespace ranges = std::ranges;
	fs::path full_path = fullPathNoValidation();
	
	// Two conditions must be satisfied for one directory (input) to be contained in another one (root):
	// 1. Input must be longer folder-wise than root
	// 2. Input must contain root at the beginning
	
	fs::path::const_iterator root_it = m_server_root_path.begin();
	fs::path::const_iterator full_it = full_path.begin();

	// C++23's ZipView would be really handy here
	while (root_it != m_server_root_path.end() && full_it != full_path.end())
	{
		// compare content
		if (*root_it != *full_it)
			return false;

		// check if full is shorter than/same size as root
		if (++full_it == full_path.end())
			return false;

		++root_it;
	}
	// all comparisons succeeded and root is longer than full
	return true;
}

} // namespace Hose