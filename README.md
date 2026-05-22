# Schnorr Signature Scheme over Z_p (Toy Implementation)

## Overview

This repository contains a **toy educational implementation** of the Schnorr Digital Signature Scheme over a finite field subgroup of (\mathbb{Z}_p^*).

The implementation demonstrates the core ideas behind:

* Key Generation
* Schnorr Identification intuition
* Fiat–Shamir transformation
* Signature generation
* Signature verification
* Modular arithmetic in finite groups

This project is intended for:

* learning cryptographic protocols,
* understanding Schnorr signatures mathematically,
* experimenting with small finite groups,
* educational demonstrations.

It is **NOT production secure** and must not be used for real cryptographic applications.

---

# Mathematical Background

We work in a subgroup of (\mathbb{Z}_p^*):

* Prime modulus: (p = 23)
* Subgroup order: (q = 11)
* Generator: (g = 2)

The public key is:

[
y = g^x \mod p
]

where:

* (x) is the secret key,
* (y) is the public key.

---

# Schnorr Signature Flow

## Key Generation

Choose secret key:

[
x \xleftarrow{$} \mathbb{Z}_q
]

Compute public key:

[
y = g^x \mod p
]

---

## Signing

Given a message (m):

### Step 1 — Choose random nonce

[
k \xleftarrow{$} \mathbb{Z}_q
]

### Step 2 — Compute commitment

[
R = g^k \mod p
]

### Step 3 — Compute challenge

In this toy implementation:

[
e = H(R, m)
]

implemented as:

[
e = (R + m) \mod q
]

### Step 4 — Compute response

[
s = k + ex \mod q
]

Signature:

[
(R, s)
]

---

## Verification

Recompute:

[
e = H(R, m)
]

Accept iff:

[
g^s \equiv R \cdot y^e \pmod p
]

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

# Example Verification Equation

The verifier checks:

[
g^s \stackrel{?}{=} R \cdot y^e \pmod p
]

Using:

[
s = k + ex
]

we get:

[
g^s = g^{k + ex}
]

[
= g^k \cdot (g^x)^e
]

[
= R \cdot y^e
]

which proves correctness.

---

# Important Security Note

This implementation is intentionally simplified and should only be used for educational purposes.

## Not Production Secure

The implementation omits several requirements necessary for real-world cryptographic security.

### 1. Tiny Parameters

The parameters:

```c
P = 23
Q = 11
```

are extremely small and trivially breakable.

Real Schnorr implementations use large secure groups.

---

### 2. Non-Cryptographic Randomness

The implementation uses:

```c
rand()
```

which is NOT cryptographically secure.

Real implementations require a CSPRNG.

---

### 3. Toy Hash Function

The challenge:

```c
e = (R + m) % Q
```

is not secure.

Real Schnorr signatures use cryptographic hash functions such as:

* SHA-256
* SHA-512
* BLAKE2
* SHAKE

Example:

```text
e = SHA256(R || m) mod q
```

---

### 4. No Serialization / Domain Separation

Real signature schemes require:

* canonical encodings,
* transcript separation,
* byte-level hashing,
* domain separation tags.

---

### 5. No Constant-Time Protection

This implementation is vulnerable to timing and side-channel attacks.

---

# Disclaimer

This repository is an educational toy implementation created for learning and experimentation.

Do not use this code in production systems, wallets, authentication systems, or security-critical environments.