#include "bm.h"

#include <stdio.h>
#include <stdlib.h>

struct BitMatrix {
    uint32_t rows;
    uint32_t cols;
    uint8_t **mat;
};

BitMatrix *bm_create(uint32_t rows, uint32_t cols) {
    BitMatrix *m = (BitMatrix *) calloc(1, sizeof(BitMatrix));
    m->rows = rows;
    m->cols = cols;
    m->mat = (uint8_t **) calloc(rows, sizeof(uint8_t *));
    uint32_t total_bytes
        = (cols % 8 == 0) ? cols / 8 : cols / 8 + 1; // if no rem, div by 8, else + 1
    if (cols == 0) { // for above statement, still need at least 1 byte
        total_bytes = 1;
    }
    for (uint32_t r = 0; r < rows; r++) {
        m->mat[r] = (uint8_t *) calloc(total_bytes, sizeof(uint8_t));
    }
    return m; // allocated memory
}

void bm_delete(BitMatrix **m) { // check if free properly
    for (uint32_t r = 0; r < bm_rows(*m); r++) {
        free((*m)->mat[r]);
    }
    free((*m)->mat);
    free(*m); // free memory
}

uint32_t bm_rows(BitMatrix *m) {
    return m->rows;
}

uint32_t bm_cols(BitMatrix *m) {
    return m->cols;
}

void bm_set_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    uint8_t mask = 1 << (c % 8); // left shift index
    m->mat[r][c / 8] = m->mat[r][c / 8] | mask; // bit | mask, sets 1
}

void bm_clr_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    uint8_t mask = ~(1 << (c % 8));
    m->mat[r][c / 8] = m->mat[r][c / 8] & mask; // bit & mask, sets 0 (clear)
}

uint8_t bm_get_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    uint8_t result = m->mat[r][c / 8];
    uint8_t mask = (1 << (c % 8)); // 1 left shift by index % 8
    result = result & mask; // bitwise and
    return result >> (c % 8); // right shift bit
}

void bm_print(BitMatrix *m) {
    for (uint32_t r = 0; r < bm_rows(m); r++) {
        for (uint32_t c = 0; c < bm_cols(m); c++) {
            printf("%u", bm_get_bit(m, r, c));
        }
        printf("\n");
    }
}
