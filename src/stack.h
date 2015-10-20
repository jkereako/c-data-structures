#include "defs.h"

#define STACK_INCREMENT 100

typedef struct stack {
  void *base;
  void *top;
  unsigned int size;
} Stack;

status init_stack(Stack *);
bool is_empty(Stack *);
status push(Stack *, void *);
status pop(Stack *, void *);
status top(Stack *, void *);

