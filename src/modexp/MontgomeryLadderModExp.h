#ifndef MONTGOMERY_LADDER_H
#define MONTGOMERY_LADDER_H
#include "IModExp.h"

class MontgomeryLadderModExp : public IModExp {
public:
    BigInt modPow(BigInt base, BigInt exp, const BigInt& mod) override {
        BigInt r0(1);
        BigInt r1 = base % mod;
        std::vector<int> bits = exp.toBinary();

        for (int i = bits.size() - 1; i >= 0; i--) {
            if (bits[i] == 0) {
                r1 = (r0 * r1) % mod;
                r0 = (r0 * r0) % mod;
            } else {
                r0 = (r0 * r1) % mod;
                r1 = (r1 * r1) % mod;
            }
        }
        return r0;
    }
    std::string getName() const override { return "Montgomery Ladder (Secure)"; }
};
#endif