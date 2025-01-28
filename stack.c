#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

int size;

void init_stack(stack *s) {
    s->top = NULL;
    size = 0;
}

void push(stack *s, int x) {
    stack_elt *elt = malloc(sizeof(*elt));
    if (elt == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    elt->x = x;
    elt->next = s->top;
    s->top = elt;
    size++;
}

int pop(stack *s) {
    if (s->top == NULL) return 0;
    stack_elt *elt = s->top;
    int popped = elt->x;
    s->top = elt->next;
    free(elt);
    size--;
    return popped;
}

int peek(stack *s) {
    if (s->top != NULL) {
        return s->top->x;
    }
    return 0;
}

void clear(stack *s) {
    while (s->top) {
        pop(s);
    }
}
