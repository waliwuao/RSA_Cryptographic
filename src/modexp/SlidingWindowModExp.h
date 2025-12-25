#ifndef SLIDING_WINDOW_MODEXP_H
#define SLIDING_WINDOW_MODEXP_H
#include "IModExp.h"
class SlidingWindowModExp : public IModExp {
public:
    BigInt modPow(BigInt base, BigInt exp, const BigInt& mod) override {
        BigInt res(1);
        BigInt b = base % mod;
        
        std::vector<BigInt> table(16);
        table[0] = BigInt(1);
        table[1] = b;
        for (int i = 2; i < 16; i++) {
            table[i] = (table[i-1] * b) % mod;
        }

        std::vector<int> bits = exp.toBinary();
        int n = bits.size();
        int i = n - 1;
        
        while (i >= 0) {
            int val = 0;
            int width = 0;
            for (int k = 0; k < 4 && i-k >= 0; k++) {
                val = (val << 1) | bits[i-k];
                width++;
            }
            
            for (int k = 0; k < width; k++) res = (res * res) % mod;
            
            if (val > 0) {
                 res = (res * table[val]) % mod;
            }
            
            i -= width;
        }
        return res;
    }
    std::string getName() const override { return "Fixed Window (4-ary) Method"; }
};
#endif