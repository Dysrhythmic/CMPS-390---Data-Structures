#include "stack.h"

int isValid(char* expr, int exprLength) {
  struct Stack pStack = newStack();
  struct Stack* pStackPtr = &pStack;
  union StackElement elem;

  for(int i = 0; i != exprLength; ++i) {
    if (expr[i] == '(') {
      elem.charValue = expr[i];
      push(pStackPtr, elem);
      }
    else if (expr[i] == ')') {
      if (isEmpty(pStackPtr)) { return 0; }
      else { pop(pStackPtr); }
    }
  }

  return isEmpty(pStackPtr);
}

// int main() {
//   char expr[] = "(2+3)*(8*9)/2)";
//   printf("%i\n", isValid(expr, sizeof(expr) - 1));
// }
