#ifndef HOSE_CONCEPTS_H
#define HOSE_CONCEPTS_H
#include <type_traits>

namespace HomeServer
{
	template<typename T>
	concept Integral = std::is_integral<T>::value;

	template<typename T>
	concept Integral64 = Integral<T> && (sizeof(T) == 8);

	template<typename T>
	concept Floating = std::is_floating_point<T>::value;

} // namespace HomeServer

#endif // HOSE_CONCEPTS_H