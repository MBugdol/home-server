#include <queryiterator.h>

template<>
std::string HomeServer::getValueFromColumn(sqlite3_stmt* stmt, size_t pos)
{
	return std::string{(char*)sqlite3_column_text(stmt, pos)};
}