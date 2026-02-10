#include <stdio.h>
#include <stdlib.h>

int flooredLog(int x, int b) {
  if (x == 0) { return 1; }
  int digits = 0;
  while (x != 0) {
    ++digits;
    x = x/b;
  }
  return digits;
}

int *digits(int x) {
  /*
  * digits returns an array of ints which represents
  *        the base 10 digits that comprise x
  *        the returned array is allocated on the heap
  *        and as such the caller takes ownership of it
  */
  int digits = flooredLog(x, 10);
  int *ret = malloc(sizeof(int)*digits);
  for (unsigned int i = digits-1; i > 0; --i, x = x/10) {
    ret[i] = x%10;
  }
  ret[0] = x; // x is now just its MSD
  return ret;
}

int main() {
  int x = 0;
  scanf("%d", &x);
  int *digs = digits(x);
  int digCount = flooredLog(x, 10);
  for (int i =0; i < digCount-1; ++i) {
    printf("%d*", digs[i]);
  }
  printf("%d\n", digs[digCount-1]);
  free(digs);
}
