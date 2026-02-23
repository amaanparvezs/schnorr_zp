#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "schnorr.h"
#include "params.h"
#include "tests.h"

int main() {
    srand(time(NULL));

    printf("=== Schnorr Signature Scheme ===\n");
    printf("=== Toy Implementation ===\n");
    printf("Public Parameters: p = %ld, q = %ld, g = %ld\n", P, Q, G);

    // (Private Key, Public Key) : (x, y)
    long x, y;

    key_gen(&x, &y);

    // Message to sign
    long message;

    printf("Enter a message to sign (as a long integer): ");
    scanf("%ld", &message);

    // Sign the message
    Signature sign = schnorr_sign(x, message);

    printf("Signature (R, s): (%ld, %ld)\n", sign.R, sign.s);

    // Verify the signature
    int valid = schnorr_verify(y, message, sign);

    if (valid) {
        printf("Signature is valid.\n");
    } else {
        printf("Signature is invalid.\n");
    }

    run_all_tests(x, y, message);

    return 0;

}