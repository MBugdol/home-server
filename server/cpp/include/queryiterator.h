#ifndef HOSE_QUERYITERATOR_H
#define HOSE_QUERYITERATOR_H

#include <sqlite3.h>
#include <debug.h>
#include <concepts.h>
#include <query.h>

namespace HomeServer
{

template<Integral T>
T getValueFromColumn(sqlite3_stmt* stmt, size_t pos)
{
	return sqlite3_column_int(stmt, pos);
}

template<Integral64 T>
T getValueFromColumn(sqlite3_stmt* stmt, size_t pos)
{
	return sqlite3_column_int64(stmt, pos);
}

template<Floating T>
T getValueFromColumn(sqlite3_stmt* stmt, size_t pos)
{
	return sqlite3_column_double(stmt, pos);
}
template<typename T>
T getValueFromColumn(sqlite3_stmt* stmt, size_t pos)
{
	static_assert(sizeof(T) != sizeof(T), "This type can't be used with SQLite queries!");
}
template<>
std::string getValueFromColumn(sqlite3_stmt* stmt, size_t pos);

template<typename T>
std::tuple<T> tupleFromStmt(sqlite3_stmt* stmt, size_t pos=0)
{
	return std::make_tuple(getValueFromColumn<T>(stmt, pos));
}

template<typename T1, typename T2, typename... Ts>
std::tuple<T1, T2, Ts...> tupleFromStmt(sqlite3_stmt* stmt, size_t pos = 0)
{
	return std::tuple_cat(tupleFromStmt<T1>(stmt, pos), tupleFromStmt<T2, Ts...>(stmt, pos + 1));
}

template<typename... Ts>
class QueryIterator
{
public:
	QueryIterator()
		: m_stmt(nullptr) {}
	QueryIterator(const Query& query)
		: m_stmt(query.m_stmt) {}
	QueryIterator begin() 
	{ 
		return *this;
	}
	QueryIterator end()
	{
		return QueryIterator{};
	}
	QueryIterator& operator=(const QueryIterator& o)
	{
		m_stmt = o.m_stmt;
	}
	friend bool operator==(const QueryIterator& l, const QueryIterator& r)
	{
		return l.m_stmt == r.m_stmt;
	}
	std::tuple<Ts...> operator*()
	{
		return tupleFromStmt<Ts...>(m_stmt);
	}
	QueryIterator& increment()
	{
		int res = sqlite3_step(m_stmt);
		if (res == SQLITE_DONE)
			m_stmt = nullptr;
		return *this;
	}
	QueryIterator& operator++()
	{
		return increment();
	}

private:
	sqlite3_stmt* m_stmt;
};

} // namespace HomeServer

#endif // HOSE_QUERYITERATOR_H