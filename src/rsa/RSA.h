#ifndef RSA_H
#define RSA_H
#include "../core/BigInt.h"
#include "../modexp/BinaryModExp.h"
#include "../multiplication/KaratsubaMultiplier.h"
class RSA {
private:
    BigInt n, e, d;
    KaratsubaMultiplier multiplier;
    BinaryModExp modExp; 
public:
    RSA(BigInt p, BigInt q, BigInt e_val, BigInt d_val);
    BigInt encrypt(const BigInt& msg);
    BigInt decrypt(const BigInt& cipher);
};
#endif