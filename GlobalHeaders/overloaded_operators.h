#ifndef _OVERLOADED_OPERATORS_H_
#define _OVERLOADED_OPERATORS_H_


#include <iostream>
#include <string>

// Wyswietlanie wektora
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& input) {
	for (auto const& x : input) {
		os << x << " ";
	}
	return os;
}




#endif //_OVERLOADED_OPERATORS_H_