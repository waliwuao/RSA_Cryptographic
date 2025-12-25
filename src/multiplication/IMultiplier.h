#ifndef IMULTIPLIER_H
#define IMULTIPLIER_H
#include "../core/BigInt.h"
class IMultiplier {
public:
    virtual ~IMultiplier() {}
    virtual BigInt multiply(const BigInt& a, const BigInt& b) = 0;
    virtual std::string getName() const = 0;
};
#endif