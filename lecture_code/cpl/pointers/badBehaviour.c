#include <stdio.h>

int main() {
  int x = 3;
  long long int z = 16 + 7 + 8589934592l + 34359738368l;
  int y = 52;
  int *p = &x;
  printf("&x: %p\n&z: %p\n&y: %p\n", &x, &z, &y);
  // All of this is undefined behavour... it is all errors, don't do it!
  for (int i = 0; i < 5; ++i, ++p) {
    printf("p currently points at: %p\n*p is: %d\n", p, *p);
  }
}
