#include "file_access.h"
#include <iostream>
#include <cassert>
#include "debug.h"
#include "directory.h"

namespace HomeServer
{
namespace fs = std::filesystem;

void FileHandler::createFolder(const std::string& folder_path_str)
{
	debug() << "Trying to create a new folder" << folder_path_str;
	Directory new_dir = {folder_path_str};
	new_dir.create();
}

} //namespace HomeServer