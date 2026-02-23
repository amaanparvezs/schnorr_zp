#include <stdio.h>
#include "schnorr.h"
#include "params.h"
#include "math.h"
#include "tests.h"

void run_all_tests(long x, long y, long message) {
    printf("\n=============================\n");
    printf("Running Schnorr Test Suite\n");
    printf("=============================\n");

    // Generate a valid signature first
    Signature sig = schnorr_sign(x, message);

    // Test 0: Valid Signature
    printf("\n[TEST 0] Valid Signature Test\n");
    int t0 = schnorr_verify(y, message, sig);
    printf("Expected: VALID | Got: %s\n", t0 ? "VALID" : "INVALID");

    // Test 1: Wrong Message
    printf("\n[TEST 1] Wrong Message Test\n");
    int t1 = schnorr_verify(y, message + 1, sig);
    printf("Expected: INVALID | Got: %s\n", t1 ? "VALID" : "INVALID");

    // Test 2: Tampered s
    printf("\n[TEST 2] Tampered s Test\n");
    Signature bad_s = sig;
    bad_s.s = (bad_s.s + 1) % Q;
    int t2 = schnorr_verify(y, message, bad_s);
    printf("Expected: INVALID | Got: %s\n", t2 ? "VALID" : "INVALID");

    // Test 3: Tampered R
    printf("\n[TEST 3] Tampered R Test\n");
    Signature bad_R = sig;
    bad_R.R = (bad_R.R + 1) % P;
    int t3 = schnorr_verify(y, message, bad_R);
    printf("Expected: INVALID | Got: %s\n", t3 ? "VALID" : "INVALID");

    // Test 4: Wrong Public Key
    printf("\n[TEST 4] Wrong Public Key Test\n");
    long fake_x = 2;
    long fake_y = mod_exp(G, fake_x, P);
    int t4 = schnorr_verify(fake_y, message, sig);
    printf("Expected: INVALID | Got: %s\n", t4 ? "VALID" : "INVALID");
}