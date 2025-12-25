#ifndef COMBA_MULTIPLIER_H
#define COMBA_MULTIPLIER_H
#include "IMultiplier.h"

class CombaMultiplier : public IMultiplier {
public:
    BigInt multiply(const BigInt& a, const BigInt& b) override {
        if (a.isZero() || b.isZero()) return BigInt(0);
        std::vector<int> res(a.size() + b.size(), 0);
        const auto& ad = a.getDigits();
        const auto& bd = b.getDigits();
        
        for (int i = 0; i < (int)res.size(); i++) {
            long long sum = 0;
            int start_j = std::max(0, i - (int)b.size() + 1);
            int end_j = std::min(i, (int)a.size() - 1);
            
            for (int j = start_j; j <= end_j; j++) {
                int k = i - j;
                sum += (long long)ad[j] * bd[k];
            }
            
            int pos = i;
            while (sum > 0) {
                if (pos >= (int)res.size()) res.push_back(0);
                sum += res[pos];
                res[pos] = sum % BigInt::getBase();
                sum /= BigInt::getBase();
                pos++;
            }
        }
        return BigInt::fromVector(res);
    }
    std::string getName() const override { return "Comba (Column-wise) O(N^2)"; }
};
#endif