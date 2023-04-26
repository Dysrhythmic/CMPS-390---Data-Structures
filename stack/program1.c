#include "stack.h"
#include "validate.h"
#include "translate.h"
#include "evaluate.h"
#include <stdio.h>
#include <string.h>

void checkExpr(char expr[]) {
  char* postfixExpr;
  int answer;

  if (isValid(expr, strlen(expr))) {
    printf("Valid expression: %s\n", expr);
    postfixExpr = translate(expr, strlen(expr));
    printf("Translation: %s\n", postfixExpr);
    answer = evaluate(postfixExpr, strlen(postfixExpr));
    printf("Answer: %i\n\n", answer);
  }
  else {
    printf("Invalid expression: %s\n\n", expr);
  }
}

int main() {
  char fileName[] = "input.txt";
  char line[MAX_SIZE];
  FILE* file;
  file = fopen(fileName, "r");
  
  while (fgets(line, sizeof(line), file)) {
    if (line[strlen(line) - 1] == '\n') { line[strlen(line) - 1] = '\0'; }
    checkExpr(line);
  }

  fclose(file);
}
