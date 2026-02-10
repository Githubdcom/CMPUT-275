#include <stdio.h>

// Below is an example of what we would need to do
// to write postfix/prefix increment as functions
int postFixInc(int *p) {
  int cpy = *p;
  *p = *p + 1;
  return cpy;
}

int preFixInc(int *p) {
  *p = *p + 1;
  return *p;
}

int main() {
  // A small note on the prefix and postfix operators ++ and --
  int x1 = 0;
  int x2 = 0;
  ++x1;
  x2++;
  // In the above there is a semantic difference, but the
  // result we observe will be the same.
  // Postfix increment/decrement mutates the given value
  //    and produces the /original/ value.
  // Prefix increment/decrement mutates the given value
  //    and produces the /new/ value.
  printf("x1: %d, x2: %d\n", x1, x2);
  int res1 = ++x1;
  int res2 = x2++;
  // In the above there is an observable difference...
  printf("x1: %d, x2: %d\n", x1, x2);
  printf("res1: %d:, res2: %d\n", res1, res2);
  res1 = --x1;
  res2 = x2--;
  printf("x1: %d, x2: %d\n", x1, x2);
  printf("res1: %d:, res2: %d\n", res1, res2);

}
