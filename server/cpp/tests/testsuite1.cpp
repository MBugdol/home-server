#include <cassert>
#include <string>

#include <directory.h>
#include <debug.h>

// test on default hose path
#undef HOSE_INSTALL_PATH

namespace Hose = HomeServer;
namespace fs = std::filesystem;

void shouldReturnTrueOnNormalPaths()
{
	const char* very_bad_valid_path = R"(aYQgNsgztlDXvkBeiLV\YIuWMrXJx\qhm/YxraQml\zdZtpdWcrdbCQUd/YfovWwL/zumtAInWL/CAjUrHOCc\rMRcadDybjsOwIMHUTQ)";
	assert(Hose::Directory{ very_bad_valid_path }.isValid() == true);
}
void shouldReturnFalseForPathsEscapingFromRootUsingDotDot()
{
	const char* escape_attempt = "../../../../../../../../../../illegal_folder";
	assert(Hose::Directory{ escape_attempt }.isValid() == false);
}
void shouldReturnFalseForPathsEscapingUsingAbsoluteDir()
{
	fs::path path = fs::current_path().root_directory() / "illegal_folder";
	assert(Hose::Directory{ path }.isValid() == false);
}

int main()
{
	shouldReturnTrueOnNormalPaths();
	shouldReturnFalseForPathsEscapingFromRootUsingDotDot();
	shouldReturnFalseForPathsEscapingUsingAbsoluteDir();
	return 0;
}