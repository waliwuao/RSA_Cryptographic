#ifndef BIGINT_H
#define BIGINT_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

class BigInt {
private:
    std::vector<int> digits;
    static const int BASE = 1000000000;
    bool sign;

public:
    BigInt();
    BigInt(long long v);
    BigInt(std::string s);

    static int getBase() { return BASE; }
    const std::vector<int>& getDigits() const { return digits; }
    int size() const { return static_cast<int>(digits.size()); }
    
    // Core
    bool isZero() const;
    bool isOdd() const;
    bool operator<(const BigInt& other) const;
    bool operator>(const BigInt& other) const;
    bool operator==(const BigInt& other) const;
    bool operator!=(const BigInt& other) const;
    bool operator<=(const BigInt& other) const;
    bool operator>=(const BigInt& other) const;

    // Arithmetic
    BigInt operator+(const BigInt& other) const;
    BigInt operator-(const BigInt& other) const;
    BigInt operator*(const BigInt& other) const;
    
    // Div/Mod
    static std::pair<BigInt, BigInt> div_mod(const BigInt& dividend, const BigInt& divisor);
    BigInt operator%(const BigInt& other) const;
    BigInt operator/(const BigInt& other) const;

    // Bitwise Helpers
    BigInt shiftLeft(int n) const;
    BigInt div2() const;
    // [NEW] Efficiently convert to binary string (0s and 1s) for ModExp
    std::vector<int> toBinary() const;
    
    // Helpers
    static void split(const BigInt& num, int k, BigInt& low, BigInt& high);
    static BigInt fromVector(const std::vector<int>& vec);
    void trim();
    static int jacobi(BigInt a, BigInt n);
    static BigInt rand(int bits);

    friend std::ostream& operator<<(std::ostream& os, const BigInt& bi);
};
#endif