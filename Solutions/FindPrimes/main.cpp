#include <omp.h>
#include <vector>
#include <iostream>

#include "../../GlobalHeaders/global_names.h"
#include "../../GlobalHeaders/prime_functions.h"
#include "../../GlobalHeaders/overloaded_operators.h"
#include "../../GlobalHeaders/string_processing.h"
#include "../../GlobalHeaders/benchmark.h"


#define NOW std::chrono::high_resolution_clock::now()

int g_INTERVAL_START = 2;
int g_INTERVAL_END = 2000000000;
int numThreads = 4;
std::string chosenAlgorithm = "";


int main(int argc, char** argv) {


	if (argc < 4) {
		std::cerr << "Sproboj: " << argv[0] << " N,M alg threadNum" << std::endl;
		std::cerr << "N,M - przedzial od N do M" << std::endl;
		std::cerr << "alg - SSE RSEF RSED SD RD" << std::endl;
		std::cerr << "threadNum - liczba watkow" << std::endl;
		exit(ARGUMENTS_EXIT);
	}

	chosenAlgorithm = argv[2];

	try {
		numThreads = atoi(argv[3]);
	}
	catch (...) {
		std::cerr << "Podano zla ilosc watkow" << std::endl;
		exit(1);
	}

	std::string interval = std::string(argv[1]);
	processInterval(interval, g_INTERVAL_START, g_INTERVAL_END);

	if (chosenAlgorithm == "SD") {
		std::cout << "SD    : " << timeFuncInvocation(1, findPrimes, g_INTERVAL_START, g_INTERVAL_END) << "[ms] / 60000 ms" << std::endl;
	}
	else if (chosenAlgorithm == "RD") {
		std::cout << "RD    : " << timeFuncInvocation(1, parallelFindPrimes, g_INTERVAL_START, g_INTERVAL_END, numThreads) << "[ms] / 60000 ms" << std::endl;
	}
	else if (chosenAlgorithm == "SSE") {
		std::cout << "SSE   : " << timeFuncInvocation(1, sieveOfEratosthenes, g_INTERVAL_START, g_INTERVAL_END) << "[ms] / 60000 ms" << std::endl;
	}
	else if (chosenAlgorithm == "RSEF") {
		std::cout << "RSE_F : " << timeFuncInvocation(1, fullSieveParallelSieveOfEratosthenes, g_INTERVAL_START, g_INTERVAL_END, numThreads) << "[ms] / 60000 ms" << std::endl;
	}
	else if (chosenAlgorithm == "RSED") {
		std::cout << "RSE_D : " << timeFuncInvocation(1, eratosthenesBlockwise, g_INTERVAL_START, g_INTERVAL_END, 128 * 1024, numThreads) << "[ms] / 60000 ms" << std::endl;
	}
	else {
		std::cerr << "Nie wybrano poprawnie algorytmu" << std::endl;
		std::cerr << "alg - SSE RSEF RSED SD RD" << std::endl;
		exit(1);
	}


	return 0;
}

