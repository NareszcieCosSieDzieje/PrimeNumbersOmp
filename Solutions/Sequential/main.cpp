#include <chrono>
#include <stdio.h>

#include "../../GlobalHeaders/global_names.h"
#include "../../GlobalHeaders/prime_functions.h"
#include "../../GlobalHeaders/overloaded_operators.h"
#include "../../GlobalHeaders/string_processing.h"
#include "../../GlobalHeaders/benchmark.h"



//=========================================================FUNCTION PROTOTYPES==================================================================\\

//=================================================================MAIN============================================================================\\

unsigned int g_INTERVAL_START = 0;
unsigned int g_INTERVAL_END = 0;

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cerr << "Za ma³o argumentów. Podaj przedzia³ liczbowy. Format: N,M\n" << std::endl;
		exit(ARGUMENTS_EXIT);
	}

	std::string interval = std::string(argv[1]);
	processInterval(interval, g_INTERVAL_START, g_INTERVAL_END);

	g_INTERVAL_START = 2;
	g_INTERVAL_END = 45000000;


	std::cout << "Podstawowy: " << timeFuncInvocation(1, findPrimes, g_INTERVAL_START, g_INTERVAL_END) << "[ms] / 60000 ms" << std::endl;

	g_INTERVAL_END = 100000000000;

	std::cout << "Sito      : " << timeFuncInvocation(1, sieveOfEratosthenes, g_INTERVAL_START, g_INTERVAL_END) << "[ms] / 60000 ms" << std::endl;


	system("pause");

	return 0;
}



//==========================================================FUNCTION DEFINITIONS=======================================================================\\


/*


std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;



/*
auto timeFuncInvocation =
[](auto&& func, auto&&... params) {

	const unsigned int numberOfRepetitions = 1; //FIXME: Du¿a liczba do uœredniania wyników

	const auto& start = std::chrono::steady_clock::now();

	for (auto i = 0; i < numberOfRepetitions; ++i) {
		std::forward<decltype(func)>(func)(std::forward<decltype(params)>(params)...);
	}

	const auto& stop = std::chrono::steady_clock::now();

	auto averageTime = (std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() / numberOfRepetitions);

	return averageTime;
};
*/

