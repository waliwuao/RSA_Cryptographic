#ifndef BINARY_MODEXP_H
#define BINARY_MODEXP_H
#include "IModExp.h"

class BinaryModExp : public IModExp {
public:
    BigInt modPow(BigInt base, BigInt exp, const BigInt& mod) override {
        BigInt res(1);
        base = base % mod;
        
        std::vector<int> bits = exp.toBinary();
        for (int bit : bits) {
            if (bit == 1) res = (res * base) % mod;
            base = (base * base) % mod;
        }
        return res; 
    }
    std::string getName() const override { return "Binary (Right-to-Left) Method"; }
};
#endif