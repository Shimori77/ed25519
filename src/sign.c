#include "ed25519.h"
#include "ge.h"
#include "sc.h"

#include <blake3.h>


void ed25519_sign(unsigned char *signature, const unsigned char *message, size_t message_len, const unsigned char *public_key, const unsigned char *private_key) {
    blake3_hasher hash;
    unsigned char hram[64];
    unsigned char r[64];
    ge_p3 R;

    blake3_hasher_init(&hash);
    blake3_hasher_update(&hash, private_key + 32, 32);
    blake3_hasher_update(&hash, message, message_len);
    blake3_hasher_finalize(&hash, r, 64);

    sc_reduce(r);
    ge_scalarmult_base(&R, r);
    ge_p3_tobytes(signature, &R);

    blake3_hasher_init(&hash);
    blake3_hasher_update(&hash, signature, 32);
    blake3_hasher_update(&hash, public_key, 32);
    blake3_hasher_update(&hash, message, message_len);
    blake3_hasher_finalize(&hash, hram, 64);

    sc_reduce(hram);
    sc_muladd(signature + 32, hram, private_key, r);
}
