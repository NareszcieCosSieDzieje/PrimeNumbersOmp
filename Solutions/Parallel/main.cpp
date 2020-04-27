#include <omp.h>
#include <vector>
#include <iostream>

#include "../../GlobalHeaders/global_names.h"
#include "../../GlobalHeaders/prime_functions.h"
#include "../../GlobalHeaders/overloaded_operators.h"
#include "../../GlobalHeaders/string_processing.h"
#include "../../GlobalHeaders/benchmark.h"


#define NOW std::chrono::high_resolution_clock::now()

int g_INTERVAL_START = 1;
int g_INTERVAL_END = 100000;


int main(int argc, char** argv) {

    if ((argc < 2) && (false)) {
		std::cerr << "Za ma³o argumentów. Podaj przedzia³ liczbowy. Format: N,M\n" << std::endl;
		exit(ARGUMENTS_EXIT);
	}

    //std::string interval = std::string(argv[1]);
	//processInterval(interval, g_INTERVAL_START, g_INTERVAL_END);

	/*
	* SD (2, 10000000) 12s
	* SD (10000000/2, 10000000) 7s
	*
	*
	*/

	g_INTERVAL_START = 2;

	g_INTERVAL_END = 2000000000;
    
	int numThreads = 4;

	//std::cout << "Sekwencyjne dzielenie     : " << timeFuncInvocation(1, findPrimes, g_INTERVAL_START, g_INTERVAL_END) << "[ms] / 60000 ms" << std::endl;

	//std::cout << "Rownolegle dzielenie      : " << timeFuncInvocation(1, parallelFindPrimes, g_INTERVAL_START, g_INTERVAL_END, numThreads) << "[ms] / 60000 ms" << std::endl;
	
	std::cout << "elo dzialam" << std::endl;


	std::cout << "Sekwencyjne Sito          : " << timeFuncInvocation(1, sieveOfEratosthenes, g_INTERVAL_START, g_INTERVAL_END) << "[ms] / 60000 ms" << std::endl;

	
	//std::cout << "Rownolegle fullSieve      : " << timeFuncInvocation(1, fullSieveParallelSieveOfEratosthenes, g_INTERVAL_START, g_INTERVAL_END, numThreads) << "[ms] / 60000 ms" << std::endl;
	

	

	//std::cout << "Sito najlepsze ultra      : " << timeFuncInvocation(1, eratosthenesBlockwise, g_INTERVAL_START, g_INTERVAL_END, 128*1024, numThreads) << "[ms] / 60000 ms" << std::endl;
	





	//std::cout << "Sito super dobre          : " << timeFuncInvocation(3, eratosthenesOdd, g_INTERVAL_START, g_INTERVAL_END, numThreads) << "[ms] / 60000 ms" << std::endl;

	//std::cout << "Rownolegle pawel          : " << timeFuncInvocation(3, fullSieveParallelSieveOfEratosthenes2, g_INTERVAL_START, g_INTERVAL_END, 100, numThreads) << "[ms] / 60000 ms" << std::endl;

	//std::cout << "Równoleg³e fullPrimes     : " << timeFuncInvocation(1, fullPrimesParallelSieveOfEratosthenes, g_INTERVAL_START, g_INTERVAL_END, numThreads) << "[ms] / 60000 ms" << std::endl;

	
	return 0;
}

