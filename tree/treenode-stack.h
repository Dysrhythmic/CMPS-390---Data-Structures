#include "tree.h"

typedef struct TreeNode TreeNode;

typedef struct Stack {
  int top;
  TreeNode* contents[MAX_SIZE];
} Stack;

Stack newStack();

int isEmpty(Stack *stack);

void push(Stack *stack, TreeNode *elem);

TreeNode* pop(Stack *stack);
