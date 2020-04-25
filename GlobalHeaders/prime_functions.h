#ifndef _PRIME_FUNCTIONS_H_
#define _PRIME_FUNCTIONS_H_

#include <iostream>
#include <string>
#include <vector>
#include <omp.h>
#include <chrono>

#include "overloaded_operators.h"



bool isPrime(unsigned int n) {
    for (unsigned int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}



// Sequential division 1/5
std::vector<unsigned int> findPrimes(unsigned int start, unsigned int end) {
    std::vector<unsigned int> primeNumbers;
    for (unsigned int i = start; i <= end; i++) {
        if (isPrime(i)) {
            primeNumbers.push_back(i);
        }
    }
    std::cout << primeNumbers.size() << std::endl;
    return primeNumbers;
}


// Sequential sieve 2/5
std::vector<int> sieveOfEratosthenes(int start, int end) {
    std::vector<int> primeNumbers;
    std::vector<bool> sieve(end - start + 1); //already initialized to false

    int sqrtN = std::sqrt(sieve.size());
    int sieveSize = sieve.size();

    for (int i = 0; i < sqrtN; i++) { // 
        if (!sieve.at(i)) {  
            int step = (start + i);
            //std::cout << "\ni = " << i << "\n_____________________" << std::endl;
            for (int y = step+i; y < sieveSize; y += step) {
                //std::cout << "y = " << y << " | val = " << start+ y <<std::endl;
                sieve.at(y) = true;
            }
        }    
    }
    
    for (int prime = 0; prime < sieveSize; prime++) {
        if(!sieve.at(prime)){
            primeNumbers.push_back(prime + start);
        }
    }
    
    //std::cout << primeNumbers.size() << std::endl;
    return primeNumbers;
}


// Parellel sieve 3/5
std::vector<unsigned int> fullPrimesParallelSieveOfEratosthenes(unsigned int start, unsigned int end, int numThreads) {
    int sieveSize = end - start + 1;
    int sqrtN = std::sqrt(sieveSize);

    std::vector<int> firstPrimes = sieveOfEratosthenes(2, std::sqrt(end));
    std::vector<unsigned int> primeNumbers;

    int firstPrimesSize = firstPrimes.size();

    //std::cout << "size = " << firstPrimes.size() << " | sqrtN = " << std::sqrt(end) << std::endl;

    omp_set_num_threads(numThreads);

    int* sieveArray = new int[sieveSize];
#pragma omp parallel for
	for (int i = 0; i < sieveSize; i++) {
        sieveArray[i] = 0;
	}

    int i = 0;
    int batch = sieveSize / numThreads;
    int batchLeftOvers = sieveSize % omp_get_num_threads();

    #pragma omp parallel private(sieveSize) //for schedule(dynamic)
    {
        int s = 0;
        int rank = omp_get_thread_num();
        int actualThreads = omp_get_num_threads();
        if (rank > 0) {
            s = (rank) * batch;
        }
        sieveSize = (rank+1) * batch;
        if (rank == actualThreads - 1) {
            sieveSize += batchLeftOvers;
            //sieveSize = sieve.size();
        }
        //std::cout << " rank = " << rank << " s = " << s << "sieveSize = " << sieveSize << std::endl;
        for (s = 0; s < sieveSize; s++) {
            for (int pi = 0; pi < firstPrimesSize; pi++) {
                int prime = firstPrimes.at(pi);
                int currentNumber = s + start;

                if (!sieveArray[s] && (currentNumber == prime)) {
                    break;
                }

                if (currentNumber < prime) {
                    break;
                }

                if (currentNumber % prime != 0) {
                    continue;
                }
                else {
#pragma omp atomic
                    sieveArray[s]++;
                    break;
                }
            }

        }
    }

    for (int prime = 0; prime < sieveSize; prime++) {
        if (!sieveArray[prime]) {
            primeNumbers.push_back(prime + start);
        }
    }

    delete[] sieveArray;
    //std::cout << "3 algo size = " << primeNumbers.size() << std::endl;
    //std::cout << "LICZBY PIERWSZE ALGO 3 YO\n" << primeNumbers << std::endl;

    return primeNumbers;
}


// Parallel sieve functional 4/5
std::vector<int> fullSieveParallelSieveOfEratosthenes(int start, int end, int numThreads) {
    int sieveSize = end - start + 1;
    int sqrtN = std::sqrt(sieveSize);    
    
    std::vector<int> firstPrimes = sieveOfEratosthenes(2, std::sqrt(end));
    int firstPrimesSize = firstPrimes.size();
    std::vector<int> used(firstPrimesSize);
    std::vector<int> primeNumbers;
   
    omp_set_num_threads(numThreads);

    int* sieveArray = new int[sieveSize];
#pragma omp parallel for 
    for (int e = 0; e < sieveSize; e++) {
        sieveArray[e] = 0;
    }

#pragma omp parallel 
    {
#pragma omp for schedule(dynamic) 
        for (int pi = 0; pi < firstPrimesSize; pi++) {
            int prime = firstPrimes.at(pi);
            int startIndex = 0;
            while ((startIndex + start) % prime != 0) {
                startIndex++;
            }
            if (startIndex + start != prime) {
                sieveArray[startIndex] = 1;
            }
            int remIndex = startIndex + prime;
            while (remIndex < sieveSize) {
                sieveArray[remIndex] = 1;
                remIndex += prime;
            }
        }
    }

    for (int prime = 0; prime < sieveSize; prime++) {
        if (sieveArray[prime] == 0) {
            primeNumbers.push_back(prime + start);
        }
    }
    
    delete[] sieveArray;
    //std::cout << "Count: " << primeNumbers.size() << std::endl;
    
    return primeNumbers;
}



 /*
bool parallelIsPrime(int n) {
    char end = 1;
    int sqrtN = std::sqrt(n);
#pragma omp parallel for schedule(dynamic)
    for (int i = 2; i <= sqrtN; i++) {
        if (n % i == 0) {
            end = 0;
        }
    }

    return end == 1 ? true : false;
}
*/

// Parallel division 5/5
std::vector<int> parallelFindPrimes(int start, int end, int numThreads) {
    std::vector<int> primeNumbers;
    omp_set_num_threads(numThreads);
#pragma omp parallel
    {
         std::vector<int> localPrimeNumbers;
#pragma omp for schedule(dynamic)
        for (int i = start; i <= end; i++) {
            if (isPrime(i)) {
                localPrimeNumbers.push_back(i);
            }
        }
#pragma omp critical
        primeNumbers.insert(primeNumbers.end(), localPrimeNumbers.begin(), localPrimeNumbers.end());
    }
    std::cout << primeNumbers.size() << std::endl;

    return primeNumbers;
}







#endif //_PRIME_FUNCTIONS_H_