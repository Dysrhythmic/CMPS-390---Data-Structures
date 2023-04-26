#include "stack.h"

char* translate(char* expr, int exprLength) {
  struct Stack postStack = newStack();
  struct Stack opStack = newStack();
  struct Stack* postStackPtr = &postStack;
  struct Stack* opStackPtr = &opStack;
  union StackElement elem;
  static char postfixExpr[MAX_SIZE];

  for(int j = 0; j != exprLength; ++j) {
    if (expr[j] >= '0' && expr[j] <= '9') {
      elem.charValue = expr[j];
      push(postStackPtr, elem);
    }
    else if (expr[j] == ')' && !isEmpty(opStackPtr)) {
      elem = pop(opStackPtr);
      push(postStackPtr, elem);
    }
    else if (expr[j] == '+' || expr[j] == '-' || expr[j] == '*' || expr[j] == '/') {
      elem.charValue = expr[j];
      push(opStackPtr, elem);
    }
  }

  while(!isEmpty(opStackPtr)) { push(postStackPtr, pop(opStackPtr)); }

  for(int j = 0; j != (postStack.top + 1); ++j) {
    postfixExpr[j] = postStack.contents[j].charValue;
  }

  postfixExpr[postStack.top + 1] = '\0';

  return postfixExpr;
}

// int main() {
//   char expr[] = "(((1 + 3) / (3 - 1)) + 5)";
//   char* postfixExpr = translate(expr, sizeof(expr)-1);
//   printf("%s\n", postfixExpr);
// }
