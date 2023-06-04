#ifndef HOSE_QUERY_H
#define HOSE_QUERY_H

#include <string>
#include <sqlite3.h>
#include <optional>

namespace HomeServer
{

template<typename... Ts>
class QueryIterator;

class Query
{
	template<typename... Ts>
	friend class QueryIterator; //< used for the QueryIterator(const Query&) constructor

public:
	Query(sqlite3* database = nullptr);
	~Query();
	void prepare(const std::string& query_string);
	void execute();
	void execute(const std::string& query_string);

	// TODO: support unsigned types too
	void bind(const int pos, const int val);
	void bind(const int pos, const long long val);
	void bind(const int pos, const double val);
	void bind(const int pos, const std::string& val);
	void bind(const int pos, const std::string&& val);

	void bind_null(const int pos);

	template<typename T>
	void bind_nullable(const int pos, const std::optional<T>& opt)
	{
		if (opt)
			bind(pos, opt.value());
		else
			bind_null(pos);
	}

private:
	std::string m_query_string;

	sqlite3* m_db; //< database handler for the query
	sqlite3_stmt* m_stmt; //< sqlite3 statement containing compiled query
};

} // namespace HomeServer

#endif // HOSE_QUERY_aH