# Schnorr Signature Scheme over Zp (Toy Implementation)

## Overview

This repository contains a toy educational implementation of the Schnorr Digital Signature Scheme over a finite field subgroup of `Zp*`.

The project demonstrates the core ideas behind:

- Key Generation
- Schnorr Signatures
- Fiat–Shamir Transformation
- Modular Arithmetic
- Signature Verification
- Challenge–Response Protocols

This implementation is intended for:

- learning cryptographic protocols,
- understanding Schnorr signatures mathematically,
- experimenting with finite groups,
- educational demonstrations.

This is **NOT production secure** and must not be used in real-world cryptographic systems.

---

# Mathematical Background

We work in a subgroup of `Zp*` with:

```text
p = 23
q = 11
g = 2
```

Where:

- `p` is a prime modulus
- `q` is the subgroup order
- `g` is a generator of the subgroup

The public key is computed as:

```text
y = g^x mod p
```

where:

- `x` = secret key
- `y` = public key

---

# Schnorr Signature Scheme

## Key Generation

Choose a secret key:

```text
x <- Zq
```

Compute the public key:

```text
y = g^x mod p
```

---

## Signing

Given a message `m`:

### Step 1 — Choose random nonce

```text
k <- Zq
```

### Step 2 — Compute commitment

```text
R = g^k mod p
```

### Step 3 — Compute challenge

In this toy implementation:

```text
e = H(R, m)
```

implemented as:

```text
e = (R + m) mod q
```

### Step 4 — Compute response

```text
s = k + ex mod q
```

The signature is:

```text
(R, s)
```

---

## Verification

Recompute:

```text
e = H(R, m)
```

Accept iff:

```text
g^s mod p == R * y^e mod p
```

---

# Why Verification Works

Since:

```text
s = k + ex
```

we get:

```text
g^s
= g^(k + ex)
= g^k * (g^x)^e
= R * y^e
```

which matches the verifier equation.

---

# Repository Structure

```text
schnorr_zp/
├── include/
│   ├── math.h
│   ├── params.h
│   └── schnorr.h
│
├── src/
│   ├── math.c
│   ├── schnorr.c
│   └── main.c
│
├── tests/
│   ├── tests.c
│   └── tests.h
│
├── debug.h
├── README.md
└── .gitignore
```

---

# Building

Compile using GCC:

```bash
gcc src/*.c tests/*.c -Iinclude -o schnorr
```

Run:

```bash
./schnorr
```

---

# Example Output

```text
Secret Key x = 7
Public Key y = 13

Message m = 5

Random nonce k = 3
Commitment R = 8

Challenge e = 2

Response s = 6

Verification Successful
```

---

# Security Notes

This implementation is intentionally simplified and should only be used for educational purposes.

## 1. Tiny Parameters

The parameters:

```text
p = 23
q = 11
```

are extremely small and trivially breakable.

Real Schnorr implementations use large secure groups.

---

## 2. Non-Cryptographic Randomness

The implementation uses:

```c
rand()
```

which is NOT cryptographically secure.

Real implementations require a CSPRNG.

---

## 3. Toy Hash Function

The challenge is computed as:

```text
e = (R + m) mod q
```

which is NOT cryptographically secure.

Real implementations use secure hash functions such as:

- SHA-256
- SHA-512
- SHAKE
- BLAKE2

For example:

```text
e = SHA256(R || m) mod q
```

---

## 4. No Constant-Time Protection

This implementation is vulnerable to timing and side-channel attacks.

---

## 5. No Serialization or Domain Separation

Real-world signature schemes require:

- canonical encodings,
- transcript separation,
- byte-level hashing,
- domain separation tags.

---

# What This Project Demonstrates Correctly

Despite being a toy implementation, the repository correctly demonstrates:

- Schnorr signing equations
- Fiat–Shamir intuition
- Challenge–response structure
- Subgroup arithmetic
- Signature verification correctness
- Relation between identification schemes and signatures

The implementation logic itself is mathematically correct.

---

# Suggested Improvements

## High Priority

- Replace toy hash with SHA-256
- Replace `rand()` with secure randomness
- Add subgroup membership checks
- Add deterministic nonce generation
- Add serialization utilities

---

## Medium Priority

- Add invalid signature tests
- Add malformed input tests
- Add negative test cases
- Add transcript abstraction

---

## Advanced Improvements

- Implement Schnorr over elliptic curves
- Add benchmark utilities
- Add formal EUF-CMA discussion
- Add transcript hashing API
- Add deterministic signing
- Add elliptic curve variant comparison

---

# Educational References

- Claus Schnorr — Identification and Signature Schemes
- Fiat–Shamir Transformation
- Schnorr Identification Protocol
- Sigma Protocols
- EUF-CMA Security Model

---

# Disclaimer

This repository is an educational toy implementation created for learning and experimentation.

Do not use this code in production systems, authentication systems, wallets, or security-critical applications.