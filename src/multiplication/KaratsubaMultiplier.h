#ifndef KARATSUBA_MULTIPLIER_H
#define KARATSUBA_MULTIPLIER_H
#include "IMultiplier.h"
#include "ClassicalMultiplier.h"
// Algorithm 4: Karatsuba O(N^1.58)
class KaratsubaMultiplier : public IMultiplier {
public:
    BigInt multiply(const BigInt& x, const BigInt& y) override {
        int n = std::max(x.size(), y.size());
        if (n < 64) { ClassicalMultiplier cm; return cm.multiply(x, y); }
        int k = n / 2;
        BigInt x0, x1, y0, y1;
        BigInt::split(x, k, x0, x1);
        BigInt::split(y, k, y0, y1);
        BigInt z0 = multiply(x0, y0);
        BigInt z2 = multiply(x1, y1);
        BigInt z1 = multiply(x0 + x1, y0 + y1) - z0 - z2;
        return z2.shiftLeft(2 * k) + z1.shiftLeft(k) + z0;
    }
    std::string getName() const override { return "Karatsuba O(N^1.58)"; }
};
#endif