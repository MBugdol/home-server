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
	void remove() const override;
	nlohmann::json json() const override;
	EntryType type() const override;
	std::string read(const uint64_t start,
		const uint64_t end);
	void append(const std::string& data);
	uint64_t size() const;
private:
};

} // namespace HomeServer

#endif // HOSE_FILE_H