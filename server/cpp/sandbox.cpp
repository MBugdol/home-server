#include <debug.h>

#include <uploadmanager.h>

using namespace HomeServer;


int main(int argc, char** argv)
{
	try {
		UploadManager um{ File{"1234.txt"} };
		
	}
	catch (const std::exception& e)
	{
		debug() << "Exception occured!";
		debug() << e.what();
		return 1;
	}
	return 0;
	
}