#include <stdio.h>

int *multiples(int n) {
  int arr[4];
  for (int i = 0; i < 4; ++i) arr[i] = (i+1)*n;
  return arr;
}

int fib(int n) {
  if (n == 1 || n == 0) {
    return 1;
  }
  return fib(n-1) + fib(n-2);
}

int main() {
  int *sevens = multiples(7);
  printf("sevens: [%d", sevens[0]);
  for (int i = 1; i < 4; ++i) {
    printf(" %d", sevens[i]);
  }
  printf("]\n");
  int *fives = multiples(5);
  printf("fives: [%d", fives[0]);
  for (int i = 1; i < 4; ++i) {
    printf(" %d", fives[i]);
  }
  printf("]\n");


  printf("sevens again: [%d", sevens[0]);
  for (int i = 1; i < 4; ++i) {
    printf(" %d", sevens[i]);
  }
  printf("]\n");
  int fib7 = fib(7);
  printf("By the way, fib(7) is %d\n", fib7);
  printf("fives: [%d", fives[0]);
  for (int i = 1; i < 4; ++i) {
    printf(" %d", fives[i]);
  }
  printf("]\n");


  printf("sevens again: [%d", sevens[0]);
  for (int i = 1; i < 4; ++i) {
    printf(" %d", sevens[i]);
  }
  printf("]\n");

}
