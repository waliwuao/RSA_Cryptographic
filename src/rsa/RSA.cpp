#include "RSA.h"
RSA::RSA(BigInt p, BigInt q, BigInt e_val, BigInt d_val) : e(e_val), d(d_val) {
    n = multiplier.multiply(p, q);
}
BigInt RSA::encrypt(const BigInt& msg) { return modExp.modPow(msg, e, n); }
BigInt RSA::decrypt(const BigInt& cipher) { return modExp.modPow(cipher, d, n); }