#include "file.h"

#include <fstream>
#include <ranges>

#include "debug.h"

namespace HomeServer
{

namespace fs = std::filesystem;

File::File(const fs::path& path)
	: Entry(path)
{
	debug();
}

void File::create() const
{
	using namespace HomeServer::EntryError;
	if (!valid())
		throw std::invalid_argument{ toString(InvalidPath) };
	if (!parentDirExists())
		throw std::invalid_argument{ toString(NoParent) };
	if (exists())
		throw std::runtime_error{ toString(AlreadyExists) };

	std::ofstream file(fullPath());
	if (!file.is_open())
		throw std::runtime_error{ "InvalidName" };
}

void File::remove() const
{
	using namespace HomeServer::EntryError;
	if (!valid())
		throw std::invalid_argument{ toString(InvalidPath) };
	if (!exists())
		throw std::invalid_argument{ toString(NonExistent) };

	fs::remove(fullPath());
}

std::string File::read(const uint64_t start,
	const uint64_t end)
{
	using namespace HomeServer::EntryError;
	if (!valid())
		throw std::invalid_argument{ toString(InvalidPath) };
	if (!exists())
		throw std::runtime_error{ toString(NonExistent) };

	std::ifstream file{ fullPath(), std::ios::in | std::ios::binary};
	file.seekg(start);
	if (!file.good())
		throw std::runtime_error("InvalidStart");

	std::string bytes;
	if (end == -1) {
		std::copy(std::istreambuf_iterator<char>(file), 
			std::istreambuf_iterator<char>(), 
			std::back_inserter(bytes));
	}
	else {
		bytes = std::string(1024 * 256, '\0');
		file.read(&bytes[0], 1024 * 256);
		bytes.resize(file.gcount());
	}
	return bytes;
}

void File::append(const std::string& data)
{
	using namespace HomeServer::EntryError;
	if (!valid())
		throw std::invalid_argument{ toString(InvalidPath) };
	if (!exists())
		throw std::runtime_error{ toString(NonExistent) };

	std::ofstream file(fullPath(), std::ios::out | std::ios::binary | std::ios::app);
	if (!file.is_open())
		throw std::runtime_error{ "FailedToOpen" };
	file << data;
}

uint64_t File::size() const
{
	return fs::file_size(fullPath());
}

nlohmann::json File::json() const
{
	nlohmann::json json = Entry::json();
	json["name"] = path().filename().string();
	json["size"] = size();
	json["type"] = "file";
	return json;
}

Entry::EntryType File::type() const
{
	return EntryType::File;
}

} // namespace HomeServer