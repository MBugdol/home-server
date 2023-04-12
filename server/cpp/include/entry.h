#ifndef HOSE_ENTRY_H
#define HOSE_ENTRY_H
#include <filesystem>
#include <string>
#include <memory>

namespace HomeServer
{

class Entry {
protected:
	typedef std::unique_ptr<Entry> EntryUniquePtr;
public:
	Entry();
	explicit Entry(const std::filesystem::path& path);
	
	[[nodiscard]] std::filesystem::path path() const;
	[[nodiscard]] bool isValid() const;
	[[nodiscard]] virtual std::string json() const = 0;
	[[nodiscard]] static EntryUniquePtr createEntryFromPath(const std::filesystem::path& path);
protected:
	[[nodiscard]] std::filesystem::path fullPath() const;
	std::filesystem::path m_path; //< a path relative to server's root
private:
	[[nodiscard]] static bool isValid(const std::filesystem::path& path);
	[[nodiscard]] static std::filesystem::path serverRootPath();
	[[nodiscard]] inline std::filesystem::path fullPathNoValidation() const noexcept;
	[[nodiscard]] bool isContainedInServerRoot() const;
private:
	static const std::filesystem::path m_server_root_path; //< server's installation directory
};

} // namespace Hose

#endif // HOSE_ENTRY_H