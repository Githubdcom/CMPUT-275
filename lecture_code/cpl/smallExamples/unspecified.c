#include <stdio.h>

int doubleNum(int *p) {
  *p = *p*2;
  return *p;
}

int addFive(int *p) {
  *p = *p + 5;
  return *p;
}

void printThree(int x, int y, int z) {
  printf("%d - %d - %d\n", x, y, z);
}

int main() {
  int x = 0;
  // What prints?
  printThree(++x, addFive(&x), doubleNum(&x));
  // Careful! The order of evaluation of comma separated expressions
  // (for example in an argument list) is /UNSPECIFIED/ meaning
  // the compiler can evaluate these three arguments in any order it
  // likes, it just must simply evaluate them before calling
  // printThree (of course).
  // For example compile this with clang versus gcc and see the
  // results.
  // Writing this code like this would be non-portable as it is
  // not the same behaviour when built on any system.
}
