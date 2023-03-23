#ifndef FILE_ACCESS_H
#define FILE_ACCESS_H
#include <filesystem>
#include <string>

namespace HomeServer {
	namespace fs = std::filesystem;
class FileHandler
{
public: // class api
	void createHomeServerDirectory();
	void createFolder(const std::string& folder_path);
private: // private methods
	/**
	 * @brief Returns the given path in a sanitized form.
	 * Converts the given string to a std::filesystem::path object and 
	 * changes the separators to the preferred ones.
	 * @param string_path the path to sanitize
	 * @return std::filesystem::path the sanitized path 
	 */
	fs::path sanitizedPath(const std::string& string_path);
	bool isContainedInRootDir(fs::path absolute_path);
	void createFolderIfNotExists(fs::path path);
	void createFolderChainTo(fs::path path);
private: // member variables 
	fs::path m_root_dir;
};

} // namespace HomeServer

#endif // FILE_ACCESS_H