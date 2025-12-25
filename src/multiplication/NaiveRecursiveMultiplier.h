#ifndef NAIVE_REC_MULTIPLIER_H
#define NAIVE_REC_MULTIPLIER_H
#include "IMultiplier.h"

class NaiveRecursiveMultiplier : public IMultiplier {
public:
    BigInt multiply(const BigInt& x, const BigInt& y) override {
        int n = std::max(x.size(), y.size());
        if (n < 4) return x * y;
        int k = n / 2;
        BigInt x0, x1, y0, y1;
        BigInt::split(x, k, x0, x1);
        BigInt::split(y, k, y0, y1);
        // (x1*B + x0) * (y1*B + y0) = x1y1*B^2 + (x1y0 + x0y1)*B + x0y0
        // 4 Multiplications required (No savings!)
        BigInt z2 = multiply(x1, y1);
        BigInt z1_a = multiply(x1, y0);
        BigInt z1_b = multiply(x0, y1);
        BigInt z0 = multiply(x0, y0);
        return z2.shiftLeft(2*k) + (z1_a + z1_b).shiftLeft(k) + z0;
    }
    std::string getName() const override { return "Naive Divide&Conquer O(N^2)"; }
};
#endif