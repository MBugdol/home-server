#include <ranges>

#include "entry.h"
#include "folder.h"
#include "file.h"
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

	//TODO: move
	if (!fs::exists(server_root_path)) 
		fs::create_directories(server_root_path);

	return server_root_path;
}
const fs::path Entry::m_server_root_path = getServerRoot();

//===\
// STATIC MEMBER FUNCTIONS
//===/

const char* EntryError::toString(const EntryErrorEnum e)
{
	switch (e)
	{
	case(NoError):
		return "NoError";
	case(InvalidPath):
		return "InvalidPath";
	case(NoParent):
		return "NoParent";
	case(AlreadyExists):
		return "AlreadyExists";
	case(NonExistent):
		return "NonExistent";
	}
}

EntryUniquePtr Entry::createEntryFromPath(
	const std::filesystem::path& path,
	const Entry::EntryType type)
{
	switch (type)
	{
	case(Entry::EntryType::File):
		return std::make_unique<File>(path);
	case(Entry::EntryType::Folder):
		return std::make_unique<Folder>(path);
	default:
		throw std::runtime_error{"EntryTypeNotDefined"};
	}
}

bool Entry::exists() const
{
	return exists(m_path);
}

bool Entry::parentDirExists() const
{
	return parentDirExists(m_path);
}

fs::path Entry::serverRootPath()
{
	return m_server_root_path;
}

bool Entry::valid(const std::filesystem::path& path)
{
	return isContainedInServerRoot(path);
}
bool Entry::exists(const std::filesystem::path& path)
{
	return fs::exists(m_server_root_path / path);
}

bool Entry::parentDirExists(const std::filesystem::path& path)
{
	return fs::exists(( m_server_root_path / path ).parent_path());
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

bool Entry::valid() const
{
	return valid(m_path);
}

nlohmann::json Entry::json() const
{
	nlohmann::json j = {
		{"path", path().string()}
	};
	return j;
}
Entry::EntryType Entry::type(const std::filesystem::path& path)
{
	if (fs::is_directory(m_server_root_path / path))
		return EntryType::Folder;
	return EntryType::File;
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
	return isContainedInServerRoot(m_path);
}

bool Entry::isContainedInServerRoot(const std::filesystem::path& path)
{
	debug() << "Checking path" << path;
	if (path.is_absolute())
	{
		debug() << "Path can't be absolute!";
		return false;
	}

	fs::path full_path = (m_server_root_path / path).lexically_normal();
	fs::path relative = full_path.lexically_relative(m_server_root_path);
	bool is_contained = std::ranges::none_of(relative, [](const fs::path& path) {return path == ".."; });
	if (!is_contained)
	{
		debug() << "Path escapes the server root!";
		return false;
	}
	debug() << "All good!";
	return true;
}

} // namespace Hose