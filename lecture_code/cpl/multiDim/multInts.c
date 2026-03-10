#include <stdio.h>
#include <stdlib.h>
// Takes two integers as command line arguments and prints their product
int sToInt(const char *s) {
  int sum = 0;
  int neg = 1;
  if (*s == '-') {
    neg = -1;
    ++s;
  }
  while (*s >= '0' && *s <= '9') {
    sum = sum*10 + *s - '0';
    ++s;
  }
  return sum*neg;
}

int main(int argc, char **argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s int1 int2\n", argv[0]);
    return 1;
  }
  printf("%d\n", sToInt(argv[1])*sToInt(argv[2]));
  // or, instead, from stdlib
  printf("%d\n", atoi(argv[1])*atoi(argv[2]));
}
