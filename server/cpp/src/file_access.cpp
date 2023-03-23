#include "file_access.h"
#include <iostream>
//#include <asio.hpp>

namespace HomeServer
{
	namespace fs = std::filesystem;

void FileHandler::createHomeServerDirectory()
{
#ifdef HOSE_INSTALL_PATH
	std::cout << "Getting root path from CMake" << std::endl;
	m_root_dir = fs::path{ HOSE_INSTALL_PATH };
#else
	std::cout << "Falling back to default installation dir" << std::endl;
	m_root_dir = fs::current_path().root_path() / "HomeServer";
#endif
	
	createFolderIfNotExists(m_root_dir);
	std::cout << "Successfuly created HoSe root under " << m_root_dir.string() << std::endl;
}

void FileHandler::createFolder(const std::string& folder_path)
{
	fs::path combined_path = m_root_dir / folder_path;
	if (combined_path != fs::weakly_canonical(combined_path))
		throw std::invalid_argument{ "The path specified ("+folder_path+") isn't canonical!" };
	createFolderIfNotExists(combined_path);
}

/*static*/ void FileHandler::createFolderIfNotExists(fs::path path)
{
	if (!fs::exists(path)) {
		try {
			fs::create_directory(path);
		}
		catch (fs::filesystem_error const& e)
		{
			std::cout << "Failed to a folder under " << path.string() << std::endl;
			throw;
		}
	}
}

} //namespace HomeServer