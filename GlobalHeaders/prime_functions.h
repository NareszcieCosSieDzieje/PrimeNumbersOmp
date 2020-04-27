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



// Sequential division 1/5 - SD
std::vector<unsigned int> findPrimes(unsigned int start, unsigned int end) {
    std::vector<unsigned int> primeNumbers;
    for (unsigned int i = start; i <= end; i++) {
        if (isPrime(i)) {
            primeNumbers.push_back(i);
        }
    }
    std::cout << "Znaleziono SD: " << primeNumbers.size() << std::endl;
    return primeNumbers;
}


// Sequential sieve 2/5 - SSE
std::vector<int> sieveOfEratosthenes(int start, int end) {
    std::vector<int> primeNumbers;
    std::vector<bool> sieve(end - start + 1); 

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
    
    std::cout << "Znaleziono SSE: " << primeNumbers.size() << std::endl;
    return primeNumbers;
}



/*std::vector<int> sieveOfEratosthenes2(int start, int end) {
    std::vector<int> primeNumbers;
    std::vector<bool> sieve(end - start + 1); //already initialized to false

    int sqrtN = std::sqrt(sieve.size());
    int sieveSize = sieve.size();

    for (int pi = 2; pi < sqrtN; pi++) {
            int startIndex = 0;
            while ((startIndex + start) % pi != 0) {
                startIndex++;
            }
            if (isPrime(startIndex + start)) {
                sieve[startIndex] = true;
            }
            int remIndex = startIndex + pi;
            while (remIndex < sieveSize) {
                sieve[remIndex] = true;
                remIndex += pi;
            }
        }
    
    for (int prime = 0; prime < sieveSize; prime++) {
        if(!sieve.at(prime)){
            primeNumbers.push_back(prime + start);
        }
    }
    
    std::cout << primeNumbers << std::endl;
    std::cout << primeNumbers.size() << std::endl;
    return primeNumbers;
}*/


//Parellel sieve 3/5 
/*std::vector<unsigned int> fullPrimesParallelSieveOfEratosthenes(unsigned int start, unsigned int end, int numThreads) {
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
//    const int batchCount = 10;

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
}*/


// Parallel sieve functional 4/5 - RSE_F
std::vector<int> fullSieveParallelSieveOfEratosthenes(int start, int end, int numThreads) {
    int sieveSize = end - start + 1;
    int sqrtN = std::sqrt(sieveSize);
    
    std::vector<int> firstPrimes = sieveOfEratosthenes(2, std::sqrt(end));
    int firstPrimesSize = firstPrimes.size();
    std::vector<int> primeNumbers;
   
    omp_set_num_threads(numThreads);

    char* sieveArray = new char[sieveSize];
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

    int found = 0;
#pragma omp parallel for reduction(+ : found)
    for (int prime = 0; prime < sieveSize; prime++) {
        found += sieveArray[prime] - 1;
    }
    
    delete[] sieveArray;
    std::cout << "Znaleziono RSE_F: " << -found << std::endl;
    
    return primeNumbers;
}


/*std::vector<int> fullSieveParallelSieveOfEratosthenes2(int start, int end, const int step, int numThreads) {
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
        //#pragma omp for schedule(dynamic) 
        int rank = omp_get_thread_num();
        
        int primeLimit = 0;
        int currentPi = 0;
        const int leftSteps = firstPrimesSize % step;
        const int stepLimit = firstPrimesSize / step;
        
        
        currentPi = (rank) * step;
        primeLimit = currentPi + step;//(rank+1) * step;

        for (int e = 0; e < stepLimit; e++) {

            for (int pi = currentPi; pi < primeLimit; pi++) {
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
            currentPi +=  numThreads * step + (rank*step);
            primeLimit += step;
            if ( (e == stepLimit - 2) && (rank == numThreads-1) ) {
                primeLimit += leftSteps;
            }
        }
    }

    int found = 0;
#pragma omp parallel for reduction(+ : found)
    for (int prime = 0; prime < sieveSize; prime++) {
        found += sieveArray[prime] - 1;
    }
    
    delete[] sieveArray;
    std::cout << "Znaleziono FS 2: " << found << std::endl;
    return primeNumbers;
}*/



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
    std::cout << "Znaleziono RD: " << primeNumbers.size() << std::endl;

    return primeNumbers;
}


// odd-only sieve
/*int eratosthenesOdd(int firstNumber, int lastNumber, char numThreads = 1)
{
    // enable/disable OpenMP
    omp_set_num_threads(numThreads);
    // instead of i*i <= lastNumber we write i <= lastNumberSquareRoot to help OpenMP
    const int lastNumberSqrt = (int)sqrt((double)lastNumber);
    int memorySize = (lastNumber - firstNumber + 1) / 2;
    // initialize
    char* isPrime = new char[memorySize + 1];
#pragma omp parallel for
    for (int i = 0; i <= memorySize; i++)
        isPrime[i] = 1;

    int firstOdd = firstNumber % 2 == 0 ? firstNumber + 1 : firstNumber;
    // find all odd non-primes
#pragma omp parallel for schedule(dynamic)
    for (int i = firstOdd; i <= lastNumberSqrt; i += 2)
        if (isPrime[i / 2])
            for (int j = i * i; j <= lastNumber; j += 2 * i)
                isPrime[j / 2] = 0;
    // sieve is complete, count primes
    int found = lastNumber >= 2 ? 1 : 0;
#pragma omp parallel for reduction(+:found)
    for (int i = 1; i <= memorySize; i++)
        found += isPrime[i];
    delete[] isPrime;

    std::cout << "Znaleziono: " << found << std::endl;
    return found;
}*/


// Parallel sieve domain 4/5 - RSE_D
int eratosthenesOddSingleBlock(const int from, const int to)
{
    const int memorySize = (to - from + 1) / 2;
    // initialize
    char* isPrime = new char[memorySize];
    for (int i = 0; i < memorySize; i++)
        isPrime[i] = 1;
    for (int i = 3; i * i <= to; i += 2)
    {
        // >>> UPDATE October 6, 2011
        // skip multiples of three: 9, 15, 21, 27, ...   
        if (i >= 3 * 3 && i % 3 == 0)
            continue;
        // skip multiples of five
        else if (i >= 5 * 5 && i % 5 == 0)
            continue;
        // skip multiples of seven
        else if (i >= 7 * 7 && i % 7 == 0)
            continue;
        // skip multiples of eleven
        else if (i >= 11 * 11 && i % 11 == 0)
            continue;
        // skip multiples of thirteen
        else if (i >= 13 * 13 && i % 13 == 0)
            continue;
        // <<< UPDATE October 6, 2011
        // skip numbers before current slice
        int minJ = ((from + i - 1) / i) * i;
        if (minJ < i * i)
            minJ = i * i;
        // start value must be odd
        if ((minJ & 1) == 0)
            minJ += i;
        // find all odd non-primes
        for (int j = minJ; j <= to; j += 2 * i)
        {
            int index = j - from;
            isPrime[index / 2] = 0;
        }
    }
    // count primes in this block
    int found = 0;
    for (int i = 0; i < memorySize; i++)
        found += isPrime[i];
    // 2 is not odd => include on demand
    if (from <= 2)
        found++;
    delete[] isPrime;
    return found;
}


// process slice-by-slice, odd numbers only
int eratosthenesBlockwise(int firstNumber, int lastNumber, int sliceSize, char numThreads = 1)
{
    //
    omp_set_num_threads(numThreads);
    int found = 0;
    // 
#pragma omp parallel for reduction(+:found)
    for (int from = firstNumber; from <= lastNumber; from += sliceSize)
    {
        int to = from + sliceSize;
        if (to > lastNumber)
            to = lastNumber;
        found += eratosthenesOddSingleBlock(from, to);
    }
    std::cout << "Znaleziono RSE_D: " << found << std::endl;
    return found;
}


/* process only odd numbers of a specified block
int eratosthenesOddSingleBlock2(const long long from, const long long to)
{
    const int memorySize = (to - from + 1) / 2;
    // initialize
    char* isPrime = new char[memorySize];
    for (int i = 0; i < memorySize; i++)
        isPrime[i] = 1;
    for (long long i = 3; i * i <= to; i += 2)
    {
        // >>> UPDATE October 6, 2011
        // skip multiples of three: 9, 15, 21, 27, ...
        if (i >= 3 * 3 && i % 3 == 0)
            continue;
        // skip multiples of five
        if (i >= 5 * 5 && i % 5 == 0)
            continue;
        // skip multiples of seven
        if (i >= 7 * 7 && i % 7 == 0)
            continue;
        // skip multiples of eleven
        if (i >= 11 * 11 && i % 11 == 0)
            continue;
        // skip multiples of thirteen
        if (i >= 13 * 13 && i % 13 == 0)
            continue;
        // skip numbers before current slice
        long long minJ = ((from + i - 1) / i) * i;
        if (minJ < i * i)
            minJ = i * i;
        // start value must be odd
        if ((minJ & 1) == 0)
            minJ += i;
        // find all odd non-primes
        for (long long j = minJ; j <= to; j += 2 * i)
        {
            long long index = j - from;
            isPrime[index / 2] = 0;
        }
    }
    // count primes in this block
    int found = 0;
    for (int i = 0; i < memorySize; i++)
        found += isPrime[i];
    // 2 is not odd => include on demand
    if (from <= 2)
        found++;
    delete[] isPrime;
    return found;
}*/


/* process slice-by-slice, odd numbers only
long long eratosthenesBlockwise2(long long firstNumber, long long lastNumber, int sliceSize, char numThreads = 1)
{
    // enable/disable OpenMP
    omp_set_num_threads(numThreads);
    long long found = 0;
    // each slices covers ["from" ... "to"], incl. "from" and "to"
#pragma omp parallel for reduction(+:found)
    for (long long from = firstNumber; from <= lastNumber; from += sliceSize)
    {
        long long to = from + sliceSize;
        if (to > lastNumber)
            to = lastNumber;
        found += eratosthenesOddSingleBlock2(from, to);
    }
    std::cout << "Znaleziono US: " << found << std::endl;
    return found;
}*/


#endif //_PRIME_FUNCTIONS_H_