#ifndef HOSE_FOLDER_H
#define HOSE_FOLDER_H

#include "entry.h"
#include <vector>
#include <memory>

namespace HomeServer
{

class Folder : public Entry
{
public:
	Folder(const std::filesystem::path& path);
	void create() const override;
private:
};

} // namespace HomeServer

#endif // HOSE_FOLDER_H