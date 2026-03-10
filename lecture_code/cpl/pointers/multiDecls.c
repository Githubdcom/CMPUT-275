#include <stdio.h>


int main() {
  int x=5, y=3;
  int* p, q;
  int *t, *z;
  printf("%d - %d\n", x, y);
  printf("sizeof p: %lu\n", sizeof(p));
  printf("sizeof q: %lu\n", sizeof(q));
  printf("sizeof t: %lu\n", sizeof(t));
  printf("sizeof z: %lu\n", sizeof(z));
}
