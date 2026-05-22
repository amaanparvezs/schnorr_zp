#include "math.h"

long mod_exp(long base, long exp, long mod) {

    long result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp / 2;
        base = (base * base) % mod;
    }
    return result;

}

long mod_mul(long a, long b, long mod) {
    return (a * b) % mod;
}