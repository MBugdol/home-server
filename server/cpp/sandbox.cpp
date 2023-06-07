#include <debug.h>

#include <uploadmanager.h>

using namespace HomeServer;


int main(int argc, char** argv)
{
	try {
		UploadManager um{ File{"123.txt"} };
		debug() << um.startUpload();
	}
	catch (const std::exception& e)
	{
		debug() << "Exception occured!";
		debug() << e.what();
		return 1;
	}
	return 0;
	
}