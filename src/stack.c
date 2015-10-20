#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define CURRENT_SIZE(stack) ((stack)-> top -(stack)->base)

status init_stack(Stack *stack) {
  stack->base = malloc(STACK_INCREMENT * sizeof(void *));

  // `malloc()` returns NULL if the space could not be allocated.
  if (stack->base == NULL) {
    return ERROR;
  }

  stack->top = stack->base;
  stack->size = STACK_INCREMENT;

  return OK;
}

bool is_empty(Stack *stack) {
  return (stack->top == stack->base) ? TRUE : FALSE;
}

status push(Stack *stack, void *data) {
  if (CURRENT_SIZE(stack) == stack->size) {
    void *new_stack = realloc(stack->base, (stack->size + STACK_INCREMENT) * sizeof(void *));

    if (new_stack == NULL) {
     return ERROR;
    }

    stack->base = new_stack;
    stack->top = stack->base + stack->size;
    stack->size += STACK_INCREMENT;
  }

  stack->top = data;
  stack->top++;
  
  return OK;
}

status pop(Stack *stack, void *data) {
  if (is_empty(stack) == TRUE) {
    return ERROR;
  }

  stack->top--;
  data = stack->top;

  return OK;
}

int main(int argc, char **argv) {
  Stack stack;

  if (init_stack(&stack) == OK) {
    printf("\n\n We're okay!");
  }
  
  return 0;
}
