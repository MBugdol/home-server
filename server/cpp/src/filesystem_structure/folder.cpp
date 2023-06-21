#include <folder.h>

#include <regex>

#include <debug.h>

namespace HomeServer
{

namespace fs = std::filesystem;
namespace ranges = std::ranges;

Folder::Folder(const fs::path& path)
	: Entry(path.string())
{
	debug();
}

void Folder::create() const
{
	using namespace HomeServer::EntryError;
	if (!valid())
		throw std::invalid_argument{ toString(InvalidPath) };
	if (!parentDirExists())
		throw std::invalid_argument{ toString(NoParent) };
	if (exists())
		throw std::runtime_error{ toString(AlreadyExists) };

	fs::create_directory(fullPath());
}

std::string Folder::name() const
{
	if (m_path.has_filename()) // ex. "qwe/123"
		return m_path.filename().string();
	else if (m_path.has_parent_path()) // ex. "qwe/123/"
		return m_path.parent_path().filename().string();
	else // empty path - return root symbol
		return "~";
}


nlohmann::json Folder::json() const
{
	nlohmann::json json = Entry::json();
	json["type"] = "directory";
	//json["size"] = size();
	json["name"] = name();
	return json;
}

Entry::EntryType Folder::type() const
{
	return EntryType::Folder;
}

nlohmann::json Folder::jsonWithChildren() const
{
	nlohmann::json json = Folder::json();
	std::vector<nlohmann::json> children_json;
	std::vector<std::unique_ptr<Entry>> children_vec = children();
	for (const auto& e : children_vec)
		children_json.push_back(e->json());
	json["children"] = children_json;
	return json;
}

std::vector<std::unique_ptr<Entry>> Folder::searchFor(const std::string& phrase) const
{
	if (!valid())
		throw std::runtime_error(EntryError::toString(EntryError::InvalidPath));
	if (!exists())
		throw std::runtime_error(EntryError::toString(EntryError::NonExistent));

	const std::regex search_regex{ R"(.*)" + phrase + R"(.*)" };
	std::vector<std::unique_ptr<Entry>> result;
	for (auto entry : fs::recursive_directory_iterator{ fullPath() })
	{
		if (!std::regex_match(entry.path().filename().string(), search_regex))
			continue;
		fs::path relpath = fs::relative(entry.path(), serverRootPath());
		if (entry.is_directory())
			result.push_back(Entry::createEntryFromPath(relpath, Entry::EntryType::Folder));
		else
			result.push_back(Entry::createEntryFromPath(relpath, Entry::EntryType::File));
	}
	return result;
}

std::vector<std::unique_ptr<Entry>> Folder::children() const
{
	if (!valid())
		throw std::runtime_error(EntryError::toString(EntryError::InvalidPath));
	if (!exists())
		throw std::runtime_error(EntryError::toString(EntryError::NonExistent));
	
	auto transformer = [&, this](const fs::directory_entry& e) -> std::unique_ptr<Entry> {
		fs::path relpath = fs::relative(e.path(), serverRootPath());
		if (e.is_directory())
			return Entry::createEntryFromPath(relpath, Entry::EntryType::Folder);
		else
			return Entry::createEntryFromPath(relpath, Entry::EntryType::File);
	};
	std::vector<std::unique_ptr<Entry>> res;
	std::ranges::copy(fs::directory_iterator{ fullPath() } | std::views::transform(transformer), std::back_inserter(res));

	return res;
}

} // namespace HomeServer