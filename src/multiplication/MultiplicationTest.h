#ifndef MULT_TEST_H
#define MULT_TEST_H
#include "IMultiplier.h"
#include "ClassicalMultiplier.h"
#include "CombaMultiplier.h"
#include "KaratsubaMultiplier.h"
#include <chrono>
#include <vector>
#include <iostream>
class MultiplicationTest {
public:
    void runBenchmarks() {
        std::cout << "=== Module 1: Big Integer Multiplication Benchmarks ===" << std::endl;
        int base_bits = 1024;
        BigInt a = BigInt::rand(base_bits);
        BigInt b = BigInt::rand(base_bits);
        for(int i=0; i<40; i++) { 
            if (i % 2 == 0) a = a + a.shiftLeft(10); 
            else b = b + b.shiftLeft(10); 
        }
        a = BigInt::rand(40000);
        b = BigInt::rand(40000);
        int benchmark_iters = 100;
        std::cout << "Test Data: " << a.size()*29 << " bits. (Running " << benchmark_iters << " iterations)" << std::endl;
        std::vector<IMultiplier*> algs;
        algs.push_back(new ClassicalMultiplier());
        algs.push_back(new CombaMultiplier());
        algs.push_back(new KaratsubaMultiplier());
        for (auto alg : algs) {
            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < benchmark_iters; i++) { alg->multiply(a, b); }
            auto end = std::chrono::high_resolution_clock::now();
            auto d = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            std::cout << "Algorithm [" << alg->getName() << "] Time: " << d.count() << " ms" << std::endl;
            delete alg;
        }
    }
};
#endif