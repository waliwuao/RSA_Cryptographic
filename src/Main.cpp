#include <iostream>
#include "multiplication/MultiplicationTest.h"
#include "modexp/ModExpTest.h"
#include "primes/PrimeTest.h"
#include "rsa/RSA.h"

int main() {
    // 1. Multiplication
    MultiplicationTest multTest;
    multTest.runBenchmarks();

    // 2. ModExp
    ModExpTest modTest;
    modTest.runBenchmarks();

    // 3. Primes
    PrimeTest primeTest;
    primeTest.runBenchmarks();

    // 4. RSA Demo
    std::cout << "\n=== Final Implementation: RSA Demo ===" << std::endl;
    BigInt p = BigInt(61); 
    BigInt q = BigInt(53); 
    BigInt e = BigInt(17); 
    BigInt d(2753);
    
    RSA rsa(p, q, e, d);
    
    BigInt msg(123);
    std::cout << "Original Message:  " << msg << std::endl;
    
    BigInt enc = rsa.encrypt(msg);
    std::cout << "Encrypted Message: " << enc << std::endl;
    
    BigInt dec = rsa.decrypt(enc);
    std::cout << "Decrypted Message: " << dec << std::endl;
    
    if (msg == dec) {
        std::cout << "[SUCCESS] Verification Passed: Decrypted message matches original." << std::endl;
    } else {
        std::cout << "[FAILURE] Verification Failed: Messages do not match!" << std::endl;
    }
    
    return 0;
}