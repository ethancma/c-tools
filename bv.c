#include "bv.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

BitVector *bv_create(uint32_t length) {
    BitVector *v = (BitVector *) calloc(1, sizeof(BitVector));
    v->length = length;
    v->vector = (uint8_t *) calloc(length, sizeof(uint8_t));
    return v; // return allocated vector
}

void bv_delete(BitVector **bv) {
    free((*bv)->vector);
    free(*bv);
    *bv = NULL; // set pointer to null;
}

uint32_t bv_length(BitVector *bv) {
    return bv->length;
}

void bv_set_bit(BitVector *bv, uint32_t i) {
    uint8_t mask = 1 << (i % 8); // set bit to 1
    bv->vector[i / 8] = bv->vector[i / 8] | mask;
}

void bv_clr_bit(BitVector *bv, uint32_t i) {
    uint8_t mask = ~(1 << (i % 8)); // set bit to 0
    bv->vector[i / 8] = bv->vector[i / 8] & mask;
}

uint8_t bv_get_bit(BitVector *bv, uint32_t i) {
    uint8_t mask = (1 << (i % 8));
    uint8_t result = bv->vector[i / 8] & mask;
    return result >> (i % 8); // right shift the bit
}

void bv_print(BitVector *bv) {
    for (uint8_t i = 0; i < bv_length(bv); i++) {
        printf("%u ", bv_get_bit(bv, i));
    }
}
