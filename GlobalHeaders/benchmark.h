#ifndef _BENCHMARK_H_
#define _BENCHMARK_H_

#include <chrono>
#include <iostream>

//TODO: numberOfRepetitions jako przekazywany argument?
template <typename FUNCTION, typename... ARGS> // typename T = unsigned int 
double timeFuncInvocation(unsigned int numberOfRepetitions, FUNCTION func, ARGS... vars) { //, T numberOfRepetitions = 1

	const auto& start = std::chrono::steady_clock::now();

	double diff = 0;

	for (unsigned int i = 0; i < numberOfRepetitions; ++i) {
		auto res = func(vars...);
	}
	
	const auto& stop = std::chrono::steady_clock::now();

	double averageTime = (std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() / numberOfRepetitions);

	return averageTime;
};


#endif //_BENCHMARK_H_