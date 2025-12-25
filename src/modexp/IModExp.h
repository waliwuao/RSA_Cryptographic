#ifndef IMODEXP_H
#define IMODEXP_H
#include "../core/BigInt.h"
class IModExp {
public:
    virtual ~IModExp() {}
    virtual BigInt modPow(BigInt base, BigInt exp, const BigInt& mod) = 0;
    virtual std::string getName() const = 0;
};
#endif