#include "stack.h"

int evaluate(char* expr, int exprLength) {
  struct Stack numStack = newStack();
  struct Stack* numStackPtr = &numStack;
  union StackElement elem;
  int j, x, y;

  for(j = 0; j != exprLength; ++j) {
    if (expr[j] >= '0' && expr[j] <= '9') {
      elem.intValue = (expr[j] - '0');
      push(numStackPtr, elem);
    }
    else {
      y = pop(numStackPtr).intValue;
      x = pop(numStackPtr).intValue;

      if (expr[j] == '+') { elem.intValue = x + y; }
      else if (expr[j] == '-') { elem.intValue = x - y; }
      else if (expr[j] == '*') { elem.intValue = x * y; }
      else if (expr[j] == '/') { elem.intValue = x / y; }

      push(numStackPtr, elem);
    }
  }

  return pop(numStackPtr).intValue;
}

// int main() {
//   char expr[] = "13+31-/5+";
//   printf("%i\n", evaluate(expr, sizeof(expr) - 1));
// }
