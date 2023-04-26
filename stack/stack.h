#define MAX_SIZE 255

union StackElement {
  int intValue;
  char charValue;
};

struct Stack {
  int top;
  union StackElement contents[MAX_SIZE];
};

struct Stack newStack();

void push(struct Stack *stack, union StackElement elem);

union StackElement pop(struct Stack *stack);

int isEmpty(struct Stack *stack);

void showStack(struct Stack *stack);

void testStack();
