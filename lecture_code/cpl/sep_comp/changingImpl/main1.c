#include <stdio.h>
// Note! Absolutely paths are not ideal because moving this
// code to another computer (or in fact even just another user) in
// this case won't work!
#include "../../../../lib/list.h"

int main() {
  struct List *l = empty();
  int x;
  while (scanf("%d", &x) == 1) {
    cons(x, l);
  }
  printList(l);
  printf("\n");
  for (int i = 0; i < length(l); ++i) {
    setIth(l, i, ith(l, i)+1);
  }

  removeIth(l, 1);
  printList(l);
  printf("\n");
  l = freeList(l);
}
