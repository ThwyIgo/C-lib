#ifndef SSTACK_H
#define SSTACK_H

/* Sequential Stack data structure.
   Simple implementation using a dynamic allocated array. It tries to be
   data type agnostic.

   You'll probably need to change some typedefs to make it work for you.
 */
#include <stdbool.h>

// Change this typedef to the type the stack will store
typedef int StackValue;

// Don't change the code below

typedef struct s_Stack *Stack;

// Creates a newStack with no elements
Stack newStack(void);

// Deletes a stack
void delStack(Stack stack);

// Add an element to the stack
void stack_push(Stack stack, StackValue value);

// Get the last element pushed to the stack and remove it from the stack
StackValue stack_pop(Stack stack);

// true if stack is empty, false otherwise
bool stack_empty(Stack stack);

#endif // SSTACK_H
