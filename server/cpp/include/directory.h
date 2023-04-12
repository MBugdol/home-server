#ifndef HOSE_DIRECTORY_H
#define HOSE_DIRECTORY_H

#include "entry.h"
#include <vector>
#include <memory>

namespace HomeServer
{

class Directory : public Entry
{
public:
	Directory(const std::filesystem::path& path);
	void create() const; //override;
	[[nodiscard]] std::vector<std::unique_ptr<Entry>> children() const;
	std::string json() const override;
private:
};

} // namespace HomeServer

#endif // HOSE_DIRECTORY_H