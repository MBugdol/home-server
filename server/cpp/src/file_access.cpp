#include "file_access.h"
#include <iostream>
#include <cassert>
#include "debug.h"
//#include <asio.hpp>

namespace HomeServer
{
	namespace fs = std::filesystem;

void FileHandler::createHomeServerDirectory()
{
#ifdef HOSE_INSTALL_PATH
	debug() << "Getting root path from CMake";
	m_root_dir = fs::path{ HOSE_INSTALL_PATH };
#else
	debug() << "Falling back to default installation dir";
	m_root_dir = fs::current_path().root_path() / "HomeServer";
#endif

	m_root_dir.make_preferred();
	m_root_dir = fs::weakly_canonical(m_root_dir);

	createFolderIfNotExists(m_root_dir);
	debug() << "Successfuly created HoSe root under" << m_root_dir.string();
}

void FileHandler::createFolder(const std::string& folder_path_str)
{
	debug() << "Trying to create a new folder" << folder_path_str;
	fs::path folder_path = sanitizedPath(folder_path_str);
	fs::path combined_path = m_root_dir / fs::path{ folder_path };

	if (!isContainedInRootDir(combined_path))
		throw std::invalid_argument{ "The path specified (" + folder_path.string() + ") is outside of the app's scope!"};

	createFolderChainTo(combined_path);
}

// =====----- PRIVATE MEMBER FUNCTIONS -----===== //

fs::path FileHandler::sanitizedPath(const std::string& string_path)
{
	fs::path path{ string_path };
	path.make_preferred();
	return path;
}

void FileHandler::createFolderIfNotExists(fs::path path)
{
	if (fs::exists(path)) return;

	try 
	{
		fs::create_directory(path);
	}
	catch (fs::filesystem_error const& e)
	{
		std::cout << "Failed to a folder under " << path.string() << std::endl;
		throw;
	}
}

void FileHandler::createFolderChainTo(fs::path path)
{
	if (fs::exists(path)) return;

	try 
	{
		fs::create_directories(path);
	}
	catch (fs::filesystem_error const& e)
	{
		std::cout << "Failed to a folder chain for " << path.string() << std::endl;
		throw;
	}
}

bool FileHandler::isContainedInRootDir(fs::path absolute_path)
{
	absolute_path = fs::weakly_canonical(absolute_path);
	debug() << "Checking if path is contained in root:" << absolute_path;
	fs::path::const_iterator root_it = m_root_dir.begin();
	fs::path::const_iterator input_it = absolute_path.begin();

	// Two conditions must be satisfied for one directory (input) to be contained in another one (root):
	// 1. Input must start with root
	// 2. Input must be longer folder-wise than root
	// Condition 1. is checked using the first if statement (while loop assures that it compares only as long as root is valid)
	// Condition 2. is checked by first incrementing the input iterator, then checking if it's beyond input's range.
	// If that's the case, then we know that input_it reached end() && root_it didn't (while clause) - input_it is shorter than root_it.
	while (root_it != m_root_dir.end())
	{
		// compare content
		if (*root_it != *input_it)
			return false;
		
		// compare folder-length
		++input_it;
		if (input_it == absolute_path.end())
			return false;

		++root_it;
	}
	return true;
}

} //namespace HomeServer