#include <accountmanager.h>
#include <debug.h>
#include <userstable.h>
#include <database.h>

int main(int argc, char** argv)
{
	using namespace HomeServer;
	AccountManager accmgr;
	int x = 100;
	while(x --> 0)
		debug() << accmgr.getRandom128BitString();
	return 0;
}