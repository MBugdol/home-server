#ifndef FILE_ACCESS_H
#define FILE_ACCESS_H
#include <filesystem>
#include <string>

namespace HomeServer {
	namespace fs = std::filesystem;
class FileHandler
{
public: // class api
	void createFolder(const std::string& folder_path);
private: // member variables 
	fs::path m_root_dir;
};

} // namespace HomeServer

#endif // FILE_ACCESS_H