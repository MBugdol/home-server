#ifndef HOSE_FOLDER_H
#define HOSE_FOLDER_H

#include "entry.h"
#include <vector>
#include <memory>
#include <vector>

namespace HomeServer
{

class Folder : public Entry
{
public:
	Folder(const std::filesystem::path& path);
	void create() const override;
	void remove() const override;
	std::string name() const;
	EntryType type() const override;

	nlohmann::json json() const override;
	nlohmann::json jsonWithChildren() const;

	std::vector<std::unique_ptr<Entry>> children() const;
	std::vector<std::unique_ptr<Entry>> searchFor(const std::string& phrase) const;
private:
};

} // namespace HomeServer

#endif // HOSE_FOLDER_H