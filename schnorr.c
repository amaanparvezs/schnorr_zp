#include <stdlib.h>
#include "params.h"
#include "schnorr.h"
#include "math.h"

void key_gen(long *x, long *y) {

    // Generate a random private key x in the range [0, Q-1]
    *x = rand() % Q;

    // Compute the public key y = g^x mod p
    *y = mod_exp(G, *x, P);

}

Signature schnorr_sign(long x, long m) {

    Signature sig;

    // Step 1: Choose a random k in the range [0, Q-1]
    long k = rand() % Q;

    // Step 2: Compute R = g^k mod p
    sig.R = mod_exp(G, k, P);

    // Step 3: Compute e = H(R || m) mod Q (using a simple hash function)
    long e = (sig.R + m) % Q;

    // Step 4: Compute s = (k - x * e) mod Q
    sig.s = (k + x * e) % Q;

    return sig;

}

int schnorr_verify(long y, long m, Signature sig) {

    // Compute e = H(R || m) mod Q
    long e = (sig.R + m) % Q;

    // Compute  g^s
    long LHS = mod_exp(G, sig.s, P);

    // Compute R * y^e
    long RHS = (sig.R * mod_exp(y, e, P)) % P;

    // Step 3: Verify  g^s == R * y^e mod p
    return (LHS == RHS);

}