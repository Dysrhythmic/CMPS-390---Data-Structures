#include <stdio.h>
#include "tree.h"

typedef struct Stack {
  int top;
  TreeNode* contents[MAX_SIZE];
} Stack;

Stack newStack() {
  Stack NewStack;
  NewStack.top = -1;
  return NewStack;
}

int isEmpty(Stack *stack) { 
  return stack->top == -1; 
}

void push(Stack *stack, TreeNode *elem) {
  if (stack->top == MAX_SIZE) { 
    printf("Error: Stack overflow\n"); 
  }
  else {
    stack->contents[++stack->top] = elem;
  }
}

TreeNode* pop(Stack *stack) {
  if (isEmpty(stack)) { 
    printf("Error: Stack underflow\n"); 
  }
  else {
    return stack->contents[stack->top--];
  }
}
