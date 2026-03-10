#include <stdio.h>
// Note! Absolutely paths are not ideal because moving this
// code to another computer (or in fact even just another user) in
// this case won't work!
#include "../../../lib/list.h"

int lt(int x, int y) {
  return x < y;
}

int gt(int x, int y) {
  return x > y;
}

int main() {
  struct List *l = empty();
  int x;
  while (scanf("%d", &x) == 1) {
    cons(x, l);
  }
  printList(l);
  printf("\n");
  sort(l, lt);
  printList(l);
  printf("\n");
  sort(l, gt);
  printList(l);
  printf("\n");
  l = freeList(l);
}
