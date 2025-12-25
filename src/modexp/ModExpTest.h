#ifndef MODEXP_TEST_H
#define MODEXP_TEST_H
#include "BinaryModExp.h"
#include "L2RBinaryModExp.h"
#include "MontgomeryLadderModExp.h"
#include "SlidingWindowModExp.h"
#include <vector>
#include <chrono>
class ModExpTest {
public:
    void runBenchmarks() {
        std::cout << "=== Module 2: Modular Exponentiation Benchmarks ===" << std::endl;
        BigInt base = BigInt::rand(512);
        BigInt exp = BigInt::rand(512);
        BigInt mod = BigInt::rand(512);
        if (!mod.isOdd()) mod = mod + BigInt(1);
        int iters = 20;
        std::cout << "Test Data: 512-bit Base/Exp/Mod (" << iters << " iterations)" << std::endl;
        std::vector<IModExp*> algs;
        algs.push_back(new BinaryModExp());
        algs.push_back(new L2RBinaryModExp());
        algs.push_back(new MontgomeryLadderModExp());
        algs.push_back(new SlidingWindowModExp());
        for (auto alg : algs) {
            auto start = std::chrono::high_resolution_clock::now();
            for(int i=0; i<iters; i++) { alg->modPow(base, exp, mod); }
            auto end = std::chrono::high_resolution_clock::now();
            auto d = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            std::cout << "Algorithm [" << alg->getName() << "] Time: " << d.count() << " ms" << std::endl;
            delete alg;
        }
    }
};
#endif