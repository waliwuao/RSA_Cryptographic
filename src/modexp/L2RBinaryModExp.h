#ifndef L2R_BINARY_MODEXP_H
#define L2R_BINARY_MODEXP_H
#include "IModExp.h"
class L2RBinaryModExp : public IModExp {
public:
    BigInt modPow(BigInt base, BigInt exp, const BigInt& mod) override {
        BigInt res(1);
        base = base % mod;
        std::vector<int> bits = exp.toBinary();
        for (int i = bits.size() - 1; i >= 0; i--) {
            res = (res * res) % mod;
            if (bits[i] == 1) res = (res * base) % mod;
        }
        return res;
    }
    std::string getName() const override { return "Binary (Left-to-Right) Method"; }
};
#endif