#ifndef PRIME_TEST_H
#define PRIME_TEST_H
#include "PrimeUtils.h"
#include <chrono>
#include <iostream>
class PrimeTest {
public:
    void runBenchmarks() {
        std::cout << "=== Module 3: Prime Generation & Algorithm Comparison ===" << std::endl;
        BigInt candidate = PrimeUtils::generatePrime(64);
        std::cout << "[Target] " << candidate << std::endl;

        std::cout << "--- Verification Speed (100 checks) ---" << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        for(int i=0; i<100; i++) { PrimeUtils::isPrimeFermat(candidate, 5); }
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Algorithm [Fermat Test]      Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        for(int i=0; i<100; i++) { PrimeUtils::isPrimeSolovayStrassen(candidate, 5); }
        end = std::chrono::high_resolution_clock::now();
        std::cout << "Algorithm [Solovay-Strassen] Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        for(int i=0; i<100; i++) { PrimeUtils::isPrimeMillerRabin(candidate, 5); }
        end = std::chrono::high_resolution_clock::now();
        std::cout << "Algorithm [Miller-Rabin]     Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
    }
};
#endif