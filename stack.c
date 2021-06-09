#include "stack.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MIN_CAPACITY 16

struct Stack {
    uint32_t top; // next empty slot
    uint32_t capacity; // number of items that can be pushed
    int64_t *items; // holds the items
};

Stack *stack_create(void) {
    Stack *s = (Stack *) calloc(1, sizeof(Stack));
    s->top = 0;
    s->capacity = MIN_CAPACITY;
    s->items = (int64_t *) calloc(s->capacity, sizeof(int64_t));
    return s;
}

void stack_delete(Stack **s) {
    free((*s)->items);
    free(*s); // free memory
    *s = NULL;
}

bool stack_empty(Stack *s) {
    return s->top == 0; // true if empty, false otherwise
}

bool stack_push(Stack *s, int64_t x) {
    if (s->top == s->capacity) {
        s->capacity *= 2; // double capacity
        s->items = (int64_t *) realloc(s->items, s->capacity * sizeof(int64_t));
        if (s->items == NULL) {
            return false; // realloc failed
        }
    }

    // set and increment next space for x
    s->items[s->top] = x;
    s->top++;
    return true;
}

bool stack_pop(Stack *s, int64_t *x) {
    if (stack_empty(s)) {
        return false;
    }
    s->top--;
    *x = s->items[s->top]; // dereference and assign value to x
    return true;
}

void stack_print(Stack *s) {
    uint32_t tracker = 0;
    while (s->top != 0) {
        printf("%13" PRId64, s->items[s->top - tracker]);
        tracker++;
    }
}
