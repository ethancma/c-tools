#include "string.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
    char *oldspeak;
    char *newspeak;
    Node *next;
    Node *prev;
};

Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (oldspeak == NULL) {
        n->oldspeak = NULL;
    } else {
        n->oldspeak = strdup(oldspeak);
    }
    if (newspeak == NULL) {
        n->newspeak = NULL;
    } else {
        n->newspeak = strdup(newspeak);
    }
    n->next = NULL;
    n->prev = NULL;
    return n; // return created null
}

void node_delete(Node **n) {
    // free memory
    if (*n) {
        free((*n)->oldspeak);
        free((*n)->newspeak);
        free(*n);
        *n = NULL;
    }
}

void node_print(Node *n) {
    if (n == NULL) {
        return;
    }
    if (n->newspeak != NULL && n->oldspeak != NULL) {
        // both new and old exists
        printf("%s -> %s\n", n->oldspeak, n->newspeak);
    }
    if (n->newspeak == NULL && n->oldspeak != NULL) {
        // newspeak doesnt exist, oldspeak exist
        printf("%s\n", n->oldspeak);
    }
}
