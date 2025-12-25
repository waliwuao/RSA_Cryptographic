#ifndef PRIME_UTILS_H
#define PRIME_UTILS_H
#include "../core/BigInt.h"
#include "../modexp/BinaryModExp.h"
class PrimeUtils {
public:
    // 1. Fermat Primality Test
    // Probabilistic: Fast but fails for Carmichael numbers
    static bool isPrimeFermat(const BigInt& n, int k = 5) {
        if (n <= BigInt(1)) return false;
        if (n == BigInt(2)) return true;
        if (!n.isOdd()) return false;
        BinaryModExp modExp;
        for(int i=0; i<k; i++) {
             BigInt a(2 + i); 
             if (modExp.modPow(a, n - BigInt(1), n) != BigInt(1)) return false;
        }
        return true;
    }

    // 2. Miller-Rabin Primality Test
    // Industrial Standard: Stronger probabilistic test
    static bool isPrimeMillerRabin(const BigInt& n, int k = 5) {
        if (n <= BigInt(1)) return false;
        if (n == BigInt(2)) return true;
        if (!n.isOdd()) return false;
        BigInt d = n - BigInt(1);
        int s = 0;
        while (!d.isOdd()) { d = d.div2(); s++; }
        BinaryModExp modExp;
        for (int i = 0; i < k; i++) {
            static const int bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
            BigInt a(bases[i % 9]);
            if (a >= n) break;
            BigInt x = modExp.modPow(a, d, n);
            if (x == BigInt(1) || x == n - BigInt(1)) continue;
            bool composite = true;
            for (int r = 1; r < s; r++) {
                x = (x * x) % n;
                if (x == n - BigInt(1)) { composite = false; break; }
            }
            if (composite) return false;
        }
        return true;
    }

    // 3. Solovay-Strassen Primality Test
    // Historical importance, uses Jacobi Symbol
    static bool isPrimeSolovayStrassen(const BigInt& n, int k = 5) {
        if (n <= BigInt(1)) return false;
        if (n == BigInt(2)) return true;
        if (!n.isOdd()) return false;
        BinaryModExp modExp;
        BigInt exponent = (n - BigInt(1)).div2();
        for (int i = 0; i < k; i++) {
            static const int bases[] = {2, 3, 5, 7, 11, 13};
            BigInt a(bases[i % 6]);
            if (a >= n) break;
            
            int jacobi = BigInt::jacobi(a, n);
            if (jacobi == 0) return false;
            
            BigInt res = modExp.modPow(a, exponent, n);
            BigInt jacobiBig = (jacobi == 1) ? BigInt(1) : (n - BigInt(1));
            
            if (res != jacobiBig) return false;
        }
        return true;
    }

    static BigInt generatePrime(int bits) {
        while (true) {
            BigInt candidate = BigInt::rand(bits);
            if (!candidate.isOdd()) candidate = candidate + BigInt(1);
            if (isPrimeMillerRabin(candidate)) return candidate;
        }
    }
};
#endif