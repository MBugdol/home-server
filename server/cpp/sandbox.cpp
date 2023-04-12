#include <debug.h>
#include <directory.h>

int main(int argc, char** argv)
{
	namespace Hose = HomeServer;
	namespace fs = std::filesystem;
	Hose::Directory dir{ "C:/HomeServer" };
	debug() << dir.json();

	return 0;
}