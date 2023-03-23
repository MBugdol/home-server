#ifndef HOSE_DEBUG_H
#define HOSE_DEBUG_H

#include <sstream>
#include <iostream>

static constexpr const char* filename_from_path(const char* path)
{
	const char* res = path;
	while (*path)
	{
		char current_ch = *path++;
		if (current_ch == '/' || current_ch == '\\')
			res = path;
	}
	return res;
}
static constexpr const char* short_funct(const char* long_funct)
{
	const char* res = long_funct;
	while (*long_funct)
	{
		if (*long_funct++ == ':')
		{
			res = long_funct;
		}
	}
	return res;
}

#define debug() \
	(Debug{}.addNoSpace("[").addNoSpace(filename_from_path(__FILE__)).addNoSpace("::").addNoSpace(__LINE__) << \
	"(").addNoSpace(short_funct(__FUNCTION__)).addNoSpace(")] ")

class Debug
{
public:
	template<typename T>
	Debug& operator<<(const T& var)
	{
		m_out << var << " ";
		return *this;
	}
	template<typename T>
	Debug& addNoSpace(const T& var)
	{
		m_out << var;
		return *this;
	}
	~Debug()
	{
		std::cerr << m_out.str() << std::endl;
	}
private:
	std::ostringstream m_out;
};

#endif // HOSE_DEBUG_H