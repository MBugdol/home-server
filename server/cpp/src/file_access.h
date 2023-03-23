#ifndef FILE_ACCESS_H
#define FILE_ACCESS_H
#include <filesystem>
#include <string>

namespace HomeServer {

class FileHandler
{
public:
	void createHomeServerDirectory();
	void createFolder(const std::string& folder_path);
private:
	static void createFolderIfNotExists(std::filesystem::path path);
	std::filesystem::path m_root_dir;
};

} // namespace HomeServer

#endif // FILE_ACCESS_H