#include <stdio.h>

#define STACK_MAX 256

typedef struct Stack Stack;
struct Stack {
    int values[STACK_MAX];
    int cur;
};

void push(Stack *stack, int val) {
    stack->values[++stack->cur] = val;
}

int main() {
    Stack *stack;
    push(stack, 5);
    push(stack, 10);
    push(stack, 7);
    push(stack, 9);
}
