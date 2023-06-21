#ifndef HOSE_ENTRY_H
#define HOSE_ENTRY_H
#include <filesystem>
#include <string>
#include <memory>
#include <nlohmann/json.hpp>

namespace HomeServer
{

namespace EntryError 
{
	enum EntryErrorEnum {
		NoError = 0,
		InvalidPath,
		NoParent,
		AlreadyExists,
		NonExistent
	};
	const char* toString(const EntryErrorEnum e);
} // namespace EntryError

class Entry;

typedef std::unique_ptr<Entry> EntryUniquePtr;

class Entry {
public: // enums
	enum class EntryType {
		File,
		Folder
	};
public:
	Entry();
	explicit Entry(const std::filesystem::path& path);

	[[nodiscard]] static EntryUniquePtr createEntryFromPath(
		const std::filesystem::path& path,
		const EntryType type
		);
	
	[[nodiscard]] std::filesystem::path path() const;
	[[nodiscard]] bool valid() const;
	[[nodiscard]] bool exists() const;
	[[nodiscard]] bool parentDirExists() const;

	virtual void create() const = 0;
	virtual EntryType type() const = 0;
	virtual nlohmann::json json() const;

	static bool valid(const std::filesystem::path& path);
	static bool exists(const std::filesystem::path& path);
	static bool parentDirExists(const std::filesystem::path& path);
protected:
	[[nodiscard]] std::filesystem::path fullPath() const;
	std::filesystem::path m_path; //< a path relative to server's root
	[[nodiscard]] static std::filesystem::path serverRootPath();
private:
	[[nodiscard]] inline std::filesystem::path fullPathNoValidation() const noexcept;
	[[nodiscard]] bool isContainedInServerRoot() const;
	[[nodiscard]] static bool isContainedInServerRoot(const std::filesystem::path& path);
private:
	static const std::filesystem::path m_server_root_path; //< server's installation directory
};

} // namespace Hose

#endif // HOSE_ENTRY_H