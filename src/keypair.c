#include "ed25519.h"
#include "ge.h"
#include <blake3.h>


void ed25519_create_keypair(unsigned char *public_key, unsigned char *private_key, const unsigned char *seed) {
    ge_p3 A;

    blake3_hasher hash;
    blake3_hasher_init(&hash);
    blake3_hasher_update(&hash, seed, 32);
    blake3_hasher_finalize(&hash, private_key, 64);

    private_key[0] &= 248;
    private_key[31] &= 63;
    private_key[31] |= 64;

    ge_scalarmult_base(&A, private_key);
    ge_p3_tobytes(public_key, &A);
}
