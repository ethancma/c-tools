#include "hash.h"

#include "ll.h"
#include "node.h"
#include "speck.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    bool mtf;
    LinkedList **lists;
};

// from asgn doc
HashTable *ht_create(uint32_t size, bool mtf) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    if (ht) {
        ht->salt[0] = 0x85ae998311115ae3; // Il nome della rosa
        ht->salt[1] = 0xb6fac2ae33a40089;
        ht->size = size;
        ht->mtf = mtf;
        ht->lists = (LinkedList **) calloc(size, sizeof(LinkedList *));
        if (!ht->lists) {
            free(ht);
            ht = NULL;
        }
    }
    return ht;
}

void ht_delete(HashTable **ht) {
    for (uint32_t i = 0; i < (*ht)->size; i++) {
        if (((*ht)->lists[i] != NULL)) {
            ll_delete(&((*ht)->lists[i]));
            // pointer nulled and free in ll_delete
        }
    }
    free((*ht)->lists);
    free(*ht);
    *ht = NULL;
}

uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

Node *ht_lookup(HashTable *ht, char *oldspeak) {
    if (oldspeak == NULL) {
        return NULL;
    }
    uint32_t index = hash(ht->salt, oldspeak) % ht_size(ht); // hash oldspeak
    return ll_lookup(ht->lists[index], oldspeak);
}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    uint32_t index = hash(ht->salt, oldspeak) % ht->size; // hash oldspeak

    if (ht->lists[index] == NULL) {
        ht->lists[index] = ll_create(ht->mtf); // create if not initialized
    }

    ll_insert(ht->lists[index], oldspeak, newspeak); // insert into linked list of hashed index
}

void ht_print(HashTable *ht) {
    for (uint32_t i = 0; i < ht->size; i++) {
        if (ht->lists[i] != NULL) {
            ll_print(ht->lists[i]);
        }
    }
}
