#include "set.h"

#include <stdbool.h>
#include <stdint.h>

typedef uint32_t Set;

Set set_empty(void) {
    return 0;
}

bool set_member(Set s, uint8_t x) {
    return (s & (1 << x)) >> x;
}

Set set_insert(Set s, uint8_t x) {
    uint32_t mask = 1 << x; // set bit at x to 1
    return s | mask;
}

Set set_remove(Set s, uint8_t x) {
    uint32_t mask = ~(1 << x); // set bit at x to 0
    return s & mask;
}

Set set_intersect(Set s, Set t) {
    return s & t; // return set with the similarities between both sets
}

Set set_union(Set s, Set t) {
    return s | t; // combine the two sets
}

Set set_complement(Set s) {
    return ~s; // return flipped set
}

Set set_difference(Set s, Set t) {
    return s & (~t); // returns the unique elements of set s
}
