#include <stdio.h>

#define MAX_SIZE 255

union StackElement {
  int intValue;
  char charValue;
};

struct Stack {
  int top;
  union StackElement contents[MAX_SIZE];
};

struct Stack newStack() {
  struct Stack NewStack;
  NewStack.top = -1;
  return NewStack;
}

int isEmpty(struct Stack *stack) { return stack->top == -1; }

void push(struct Stack *stack, union StackElement elem) {
  if (stack->top == MAX_SIZE) { printf("Error: Stack overflow\n"); }
  
  stack->contents[++stack->top] = elem;
}

union StackElement pop(struct Stack *stack) {
  union StackElement elem;
  
  if (isEmpty(stack)) { printf("Error: Stack underflow\n"); }

  elem = stack->contents[stack->top--];
  return elem;
}

void showStack(struct Stack *stack) {
  for (int j = 0; j != (stack->top + 1); ++j) {
    if (stack->contents[j].charValue) {
      printf("%c ", stack->contents[j].charValue);
    }
    else {
      printf("%i ", stack->contents[j].intValue);
    }
  }
  printf("\n");
}

int runTest(int received, int expected, int testCount, int testsPassed) {
  if (expected == received) { testsPassed++; }
  else { printf("Test %d Failed: Expected %d but got %d\n", testCount, expected, received); }
  return testsPassed;
}

void testStack() {
  int testsPassed = 0;
  int testCount = 1;
  struct Stack testStack = newStack();
  struct Stack *testStackPtr = &testStack;

  testsPassed = runTest(isEmpty(testStackPtr), 1, testCount, testsPassed);
  testCount++;

  union StackElement a;
  a.intValue = 5;
  push(testStackPtr, a);
  testsPassed = runTest(isEmpty(testStackPtr), 0, testCount, testsPassed);
  testCount++;

  union StackElement b;
  b.charValue = 'a';
  push(testStackPtr, b);
  testsPassed = runTest(pop(testStackPtr).charValue, 'a', testCount, testsPassed);
  testCount++;

  testsPassed = runTest(testStack.contents[testStack.top].intValue, 5, testCount, testsPassed);

  printf("%d/%d tests passed\n", testsPassed, testCount);
}

int main() {
  testStack();
}
