#include <omp.h>
#include <vector>
#include <iostream>

std::vector<unsigned int> sieveOfEratosthenes(unsigned int start, unsigned int end);

int main(int argc, char** argv) {



    printf("elo\n");
	return 0;
}


std::vector<unsigned int> sieveOfEratosthenes(unsigned int start, unsigned int end) {
    std::vector<unsigned int> primeNumbers;
    std::vector<bool> sieve(end - start + 1); //already initialized to false

    unsigned int sqrtN = std::sqrt(sieve.size());
    unsigned int sieveSize = sieve.size();

    for (unsigned int i = 0; i < sqrtN; i++) { // 
        if (!sieve.at(i)) {
            unsigned int step = (start + i);
            //std::cout << "\ni = " << i << "\n_____________________" << std::endl;
            for (unsigned int y = step + i; y < sieveSize; y += step) {
                //std::cout << "y = " << y << " | val = " << start+ y <<std::endl;
                sieve.at(y) = true;
            }
        }
    }

    for (unsigned int prime = 0; prime < sieveSize; prime++) {
        if (!sieve.at(prime)) {
            primeNumbers.push_back(prime + start);
        }
    }

    std::cout << primeNumbers.size() << std::endl;
    return primeNumbers;
}
