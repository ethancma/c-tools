#include "ll.h"

#include "node.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct LinkedList {
    uint32_t length;
    Node *head;
    Node *tail;
    bool mtf;
};

LinkedList *ll_create(bool mtf) {
    LinkedList *ll = (LinkedList *) malloc(sizeof(LinkedList));
    ll->length = 0;
    ll->mtf = mtf;
    ll->head = node_create(NULL, NULL); // allocate memory and create node
    ll->tail = node_create(NULL, NULL);
    ll->head->next = ll->tail;
    ll->tail->prev = ll->head;
    return ll; // return created linked list
}

// referenced from professor's slides
void ll_delete(LinkedList **ll) {
    //free memory
    while ((*ll)->head != NULL) { // check that the list is not empty
        Node *temp = NULL;
        temp = (*ll)->head->next;

        if ((*ll)->head != NULL) { // free if node exists
            node_delete(&(*ll)->head->prev);
            (*ll)->head->prev = NULL;
        }

        (*ll)->head = temp; // get next node
    }

    node_delete(&(*ll)->tail);
    free(*ll);
    *ll = NULL;
}

uint32_t ll_length(LinkedList *ll) {
    return ll->length;
}

Node *ll_lookup(LinkedList *ll, char *oldspeak) {
    // check if oldspeak and linked list are null
    if (oldspeak == NULL || ll == NULL) {
        return NULL;
    }
    for (Node *n = ll->head->next; n != ll->tail; n = n->next) {
        if (n->oldspeak == NULL) {
            return NULL;
        }
        if (strcmp(n->oldspeak, oldspeak) == 0) { // if they are equal
            if (ll->mtf) {

                // move current to front of list
                n->prev = ll->head; // current previous is now the head
                n->next = ll->head->next; // current next points to the head next

                n->prev->next = n->next; // set current prev next to the current next
                n->next->prev = n->prev; // set the current next prev to the current prev

                ll->head->next->prev = n; // head next prev now points at current
                ll->head->next = n; // head next now points at current
            }
            return n; // found and return pointer
        } // referenced from professor's slides
    }
    return NULL; // not in linked list
}

// referenced from Eugene/Sahiti
void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
    if (ll_lookup(ll, oldspeak) == NULL) {
        Node *temp = node_create(oldspeak, newspeak);

        // rearrange pointers to put at head of list
        temp->next = ll->head->next;
        temp->prev = ll->head;
        ll->head->next->prev = temp;
        ll->head->next = temp;
        ll->length++;
    }
}

void ll_print(LinkedList *ll) {
    for (Node *n = ll->head->next; n != NULL; n = n->next) {
        node_print(n);
    }
}
