#include "list.h"
#include <stdlib.h>
int main() {
  struct List l;
  initList(&l);
  cons(1, cons(2, cons(3, &l)));
  struct List *l2 = malloc(sizeof(struct List));
  initList(l2);
  cons(7, cons(8, cons(9, cons(10, l2))));
  printList(&l);
  printList(l2);
  freeList(&l);
  freeList(l2);
  free(l2);
}
