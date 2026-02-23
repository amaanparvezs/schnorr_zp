#ifndef SCHNORR_H
#define SCHNORR_H

typedef struct {
    long R;
    long s;
} Signature;

void key_gen(long *x, long *y);

Signature schnorr_sign(long x, long m);

int schnorr_verify(long y, long m, Signature sig);

#endif