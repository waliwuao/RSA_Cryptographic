#ifndef CLASSICAL_MULTIPLIER_H
#define CLASSICAL_MULTIPLIER_H
#include "IMultiplier.h"

class ClassicalMultiplier : public IMultiplier {
public:
    BigInt multiply(const BigInt& a, const BigInt& b) override {
        return a * b; 
    }
    std::string getName() const override { return "Classical (Row-wise) O(N^2)"; }
};
#endif