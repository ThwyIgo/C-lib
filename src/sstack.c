#include "thw/sstack.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct s_Stack
{
    long last;
    StackValue *content;
} * Stack;

Stack newStack(void)
{
    Stack ret = malloc(sizeof(struct s_Stack));
    *ret = (struct s_Stack){ -1, NULL };
    return ret;
}

void delStack(Stack stack)
{
    free(stack->content);
    free(stack);
}

void stack_push(Stack stack, StackValue value)
{
    stack->content =
      realloc(stack->content, (++stack->last + 1) * sizeof(StackValue));
    stack->content[stack->last] = value;
}

StackValue stack_pop(Stack stack)
{
    StackValue ret = stack->content[stack->last];
    if (stack->last == 0) {
        free(stack->content);
        stack->content = NULL;
    } else
        stack->content =
          realloc(stack->content, stack->last * sizeof(StackValue));
    stack->last--;
    return ret;
}

bool stack_empty(Stack stack)
{
    return stack->last == -1;
}
