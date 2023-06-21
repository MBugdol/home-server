#include <debug.h>
#include <filesystem>
#include <ranges>

#include <folder.h>

using namespace HomeServer;
namespace fs = std::filesystem;

int main(int argc, char** argv)
{
	try {
		Folder f{ " " };
		debug() << f.jsonWithChildren();
	}
	catch (const std::exception& e)
	{
		debug() << "Exception occured!";
		debug() << e.what();
		return 1;
	}
	return 0;
	
}