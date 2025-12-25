#include "BigInt.h"
#include <sstream>
#include <algorithm>
#include <random>

BigInt::BigInt() : sign(false) {}
BigInt::BigInt(long long v) {
    if (v < 0) { sign = true; v = -v; } else { sign = false; }
    if (v == 0) digits.push_back(0);
    while (v > 0) {
        digits.push_back(static_cast<int>(v % BASE));
        v /= BASE;
    }
}
BigInt::BigInt(std::string s) {
    sign = false;
    if (s.length() == 0) { digits.push_back(0); return; }
    int pos = 0;
    if (s[0] == '-') { sign = true; pos = 1; }
    int len = static_cast<int>(s.length());
    for (int i = len; i > pos; i -= 9) {
        if (i < pos + 9)
            digits.push_back(std::stoi(s.substr(pos, i - pos)));
        else
            digits.push_back(std::stoi(s.substr(i - 9, 9)));
    }
    trim();
}

bool BigInt::isZero() const { return digits.empty() || (digits.size() == 1 && digits[0] == 0); }
bool BigInt::isOdd() const { return !digits.empty() && (digits[0] % 2 != 0); }
bool BigInt::operator<(const BigInt& other) const {
    if (digits.size() != other.digits.size()) return digits.size() < other.digits.size();
    for (int i = static_cast<int>(digits.size()) - 1; i >= 0; i--)
        if (digits[i] != other.digits[i]) return digits[i] < other.digits[i];
    return false;
}
bool BigInt::operator>(const BigInt& other) const { return other < *this; }
bool BigInt::operator==(const BigInt& other) const { return !(*this < other) && !(other < *this); }
bool BigInt::operator!=(const BigInt& other) const { return !(*this == other); }
bool BigInt::operator<=(const BigInt& other) const { return !(*this > other); }
bool BigInt::operator>=(const BigInt& other) const { return !(*this < other); }

BigInt BigInt::operator+(const BigInt& other) const {
    BigInt res;
    int carry = 0;
    size_t n = std::max(digits.size(), other.digits.size());
    for (size_t i = 0; i < n || carry; ++i) {
        int val1 = (i < digits.size()) ? digits[i] : 0;
        int val2 = (i < other.digits.size()) ? other.digits[i] : 0;
        int sum = carry + val1 + val2;
        if (sum >= BASE) { carry = 1; sum -= BASE; } else { carry = 0; }
        res.digits.push_back(sum);
    }
    return res;
}

BigInt BigInt::operator-(const BigInt& other) const {
    BigInt res;
    int borrow = 0;
    for (size_t i = 0; i < digits.size(); ++i) {
        int val2 = (i < other.digits.size()) ? other.digits[i] : 0;
        int sub = digits[i] - borrow - val2;
        if (sub < 0) { sub += BASE; borrow = 1; } else { borrow = 0; }
        res.digits.push_back(sub);
    }
    res.trim();
    return res;
}

BigInt BigInt::operator*(const BigInt& other) const {
    if (isZero() || other.isZero()) return BigInt(0);
    BigInt res;
    res.digits.resize(digits.size() + other.digits.size(), 0);
    for (size_t i = 0; i < digits.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < other.digits.size() || carry; ++j) {
            long long cur = res.digits[i + j] + 
                            static_cast<long long>(digits[i]) * (j < other.digits.size() ? other.digits[j] : 0) + carry;
            res.digits[i + j] = static_cast<int>(cur % BASE);
            carry = static_cast<int>(cur / BASE);
        }
    }
    res.trim();
    return res;
}

std::pair<BigInt, BigInt> BigInt::div_mod(const BigInt& dividend, const BigInt& divisor) {
    if (divisor.isZero()) throw std::runtime_error("Division by zero");
    if (dividend < divisor) return {BigInt(0), dividend};
    if (dividend == divisor) return {BigInt(1), BigInt(0)};
    BigInt quotient, remainder;
    quotient.digits.resize(dividend.size(), 0);
    remainder = BigInt(0);
    for (int i = static_cast<int>(dividend.digits.size()) - 1; i >= 0; i--) {
        remainder = remainder.shiftLeft(1);
        remainder.digits[0] = dividend.digits[i];
        remainder.trim();
        int l = 0, r = BASE - 1, best = 0;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (divisor * BigInt(mid) <= remainder) { best = mid; l = mid + 1; } 
            else { r = mid - 1; }
        }
        quotient.digits[i] = best;
        remainder = remainder - (divisor * BigInt(best));
    }
    quotient.trim();
    return {quotient, remainder};
}

BigInt BigInt::operator%(const BigInt& other) const { return div_mod(*this, other).second; }
BigInt BigInt::operator/(const BigInt& other) const { return div_mod(*this, other).first; }

BigInt BigInt::shiftLeft(int n) const {
    if (n == 0) return *this;
    if (isZero()) return *this;
    BigInt res = *this;
    res.digits.insert(res.digits.begin(), static_cast<size_t>(n), 0);
    return res;
}

BigInt BigInt::div2() const {
    BigInt res;
    int remainder = 0;
    for (int i = static_cast<int>(digits.size()) - 1; i >= 0; i--) {
        long long cur = digits[i] + remainder * 1LL * BASE;
        res.digits.push_back(static_cast<int>(cur / 2));
        remainder = cur % 2;
    }
    std::reverse(res.digits.begin(), res.digits.end());
    res.trim();
    return res;
}

std::vector<int> BigInt::toBinary() const {
    std::vector<int> bits;
    if (isZero()) return bits;
    BigInt temp = *this;

    while (!temp.isZero()) {
        bits.push_back(temp.isOdd() ? 1 : 0);
        temp = temp.div2();
    }
    return bits;
}

void BigInt::split(const BigInt& num, int k, BigInt& low, BigInt& high) {
    int n = num.size();
    if (k >= n) { low = num; high = BigInt(0); return; }
    std::vector<int> l(num.digits.begin(), num.digits.begin() + k);
    std::vector<int> h(num.digits.begin() + k, num.digits.end());
    low = BigInt::fromVector(l);
    high = BigInt::fromVector(h);
}

BigInt BigInt::fromVector(const std::vector<int>& vec) { BigInt b; b.digits = vec; b.trim(); return b; }
void BigInt::trim() { while (digits.size() > 1 && digits.back() == 0) digits.pop_back(); }

int BigInt::jacobi(BigInt a, BigInt n) {
    if (n <= BigInt(0) || !n.isOdd()) return 0;
    a = a % n;
    int t = 1;
    while (!a.isZero()) {
        while (!a.isOdd()) {
            a = a.div2();
            int n_mod_8 = n.getDigits()[0] % 8;
            if (n_mod_8 == 3 || n_mod_8 == 5) t = -t;
        }
        if (a < n) { std::swap(a, n); if (a.getDigits()[0] % 4 == 3 && n.getDigits()[0] % 4 == 3) t = -t; }
        a = a - n;
    }
    return (n == BigInt(1)) ? t : 0;
}

BigInt BigInt::rand(int bits) {
    BigInt res;
    int numDigits = bits / 29 + 1;
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, BASE - 1);
    res.digits.resize(numDigits);
    for(int i=0; i<numDigits; i++) res.digits[i] = dis(gen);
    res.trim();
    if (res.isZero()) return BigInt(1);
    return res;
}

std::ostream& operator<<(std::ostream& os, const BigInt& bi) {
    if (bi.isZero()) { os << "0"; return os; }
    os << bi.digits.back();
    for (int i = static_cast<int>(bi.digits.size()) - 2; i >= 0; i--) os << std::setfill('0') << std::setw(9) << bi.digits[i];
    return os;
}