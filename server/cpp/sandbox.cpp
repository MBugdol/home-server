#include <debug.h>
#include <filesystem>
#include <ranges>

#include <folder.h>
#include <file.h>

using namespace HomeServer;
namespace fs = std::filesystem;

int main(int argc, char** argv)
{
	try {
		File f{ "cat.jpg" };
		debug() << f.read(0, -1);
	}
	catch (const std::exception& e)
	{
		debug() << "Exception occured!";
		debug() << e.what();
		return 1;
	}
	return 0;
	
}