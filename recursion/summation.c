#include <stdio.h>

int consecutiveSum(int n) {
  if (n == 1) { return 1; }
  else { return n + consecutiveSum(n - 1); }
}

int main() {
  int n = 6;
  int consecSum = consecutiveSum(n);
  printf("%d\n", consecSum);
}