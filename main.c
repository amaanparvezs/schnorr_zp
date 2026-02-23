#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "schnorr.h"

int main() {
    srand(time(NULL));

    // (Private Key, Public Key) : (x, y)
    long x, y;

    key_gen(&x, &y);

    printf("Private Key (x): %ld\n", x);
    printf("Public Key (y): %ld\n", y);

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

    return 0;

}