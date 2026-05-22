#include <stdio.h>
#include <stdlib.h>
#include "params.h"
#include "schnorr.h"
#include "math.h"
#include "debug.h"

void key_gen(long *x, long *y) {
    LOG("\n=== KEY GENERATION ===\n");

    // Generate a random private key x in the range [1, Q-1]
    *x = rand() % (Q - 1) + 1; // to avoid x = 0
    LOG("Private key x = %ld\n", *x);

    // Compute the public key y = g^x mod p
    *y = mod_exp(G, *x, P);
    LOG("Public key y = g^x mod p = %ld\n", *y);

}

Signature schnorr_sign(long x, long m) {
    LOG("\n=== SIGNING ===\n");
    LOG("Message m = %ld\n", m);

    Signature sig;

    // Choose a random k in the range [0, Q-1]
    long k = rand() % (Q - 1) + 1; // to avoid k = 0
    LOG("Chosen nonce k = %ld\n", k);

    // Compute R = g^k mod p
    sig.R = mod_exp(G, k, P);
    LOG("Commitment R = g^k mod p = %ld\n", sig.R);

    // Compute e = H(R || m) mod Q (using a simple hash function)
    long e = ((sig.R + m) % Q + Q) % Q;
    LOG("Challenge e = H(R, m) mod q = %ld\n", e);

    // Compute s = (k + x * e) mod Q
    sig.s = (k + x * e) % Q;
    LOG("Response s = (k + e * x) mod q = %ld\n", sig.s);

    return sig;

}

int schnorr_verify(long y, long m, Signature sig) {
    LOG("\n=== VERIFICATION ===\n");

    LOG("R = %ld\n", sig.R);
    LOG("s = %ld\n", sig.s);

    // Compute e = H(R || m) mod Q
    long e = (sig.R + m) % Q;
    LOG("e = %ld\n", e);

    // Compute  g^s
    long LHS = mod_exp(G, sig.s, P);
    LOG("LHS = g^s mod p = %ld\n", LHS);

    // Compute R * y^e
    long RHS = (sig.R * mod_exp(y, e, P)) % P;
    LOG("RHS = R * y^e mod p = %ld\n", RHS);

    // Verify  g^s == R * y^e mod p
    LOG("Checking equation: g^s == R * y^e ?\n");
    LOG("%ld == %ld\n", LHS, RHS);
    return (LHS == RHS);

}