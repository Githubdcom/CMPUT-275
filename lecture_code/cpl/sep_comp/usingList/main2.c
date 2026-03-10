#include "../../../../lib/list.h"
int main() {
  struct List *l = empty();
  cons(1, cons(2, cons(3, l)));
  printList(l);
  freeList(l);
}
