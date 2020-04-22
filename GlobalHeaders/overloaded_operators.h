#ifndef _OVERLOADED_OPERATORS_H_
#define _OVERLOADED_OPERATORS_H_


#include <iostream>
#include <string>

// Wyswietlanie wektora
std::ostream& operator<<(std::ostream& os, const std::vector<int>& input) {
	for (auto const& x : input) {
		os << x << " ";
	}
	return os;
}




#endif //_OVERLOADED_OPERATORS_H_