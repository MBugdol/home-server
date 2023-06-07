#ifndef HOSE_FILE_H
#define HOSE_FILE_H

#include "entry.h"

namespace HomeServer
{

class File : public Entry
{
public:
	File(const std::filesystem::path& path);
	void create() const override;
private:
};

} // namespace HomeServer

#endif // HOSE_FILE_H