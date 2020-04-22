#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <string>

/*
#include "prime_functions.h"
#include "overloaded_operators.h"
#include "string_processing.h"
*/

#include "../OMP_Prime_Numbers/prime_functions.h"
#include "../OMP_Prime_Numbers/overloaded_operators.h"
#include "../OMP_Prime_Numbers/string_processing.h"
#include "../OMP_Prime_Numbers/global_names.h"

//=========================================================FUNCTION PROTOTYPES==================================================================\\


//strerror(errno)


//=================================================================MAIN============================================================================\\

//FIXME: jakie przedzia³y wartosci
int g_INTERVAL_START = 0;
int g_INTERVAL_END = 0;

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cerr << "Za ma³o argumentów. Podaj przedzia³ liczbowy. Format: N,M\n" << std::endl;
		//TODO: exit 
	}

	std::string interval = std::string(argv[1]);
	processInterval(interval, g_INTERVAL_START, g_INTERVAL_END);

	std::cout << "Sito      : " << sieveOfEratosthenes(g_INTERVAL_START, g_INTERVAL_END) << std::endl;
	std::cout << "Podstawowy: " << findPrimes(g_INTERVAL_START, g_INTERVAL_END) << std::endl;
	


	std::cout << "Witamy w rownoleglej rzeczywistosci!" << std::endl;
#pragma omp parallel
	{
		std::cout << "elo\t" << std::endl;
	}

	
	system("pause");

	return 0;
}



//==========================================================FUNCTION DEFINITIONS=======================================================================\\
