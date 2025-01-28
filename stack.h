#ifndef STACK_H_
#define STACK_H_

typedef struct stack_elt_tag {
    int x;
    struct stack_elt_tag *next;
} stack_elt;

typedef struct {
    stack_elt *top;
} stack;

// Function declarations for stack operations
void init_stack(stack *s);
void push(stack *s, int x);
int pop(stack *s);
int peek(stack *s);
void clear(stack *s);

#endif  // STACK_H_
