#include "tree.h"
#include <stdio.h>
int main() {
  struct BTree *t = empty();
  int x = 0;
  while (scanf("%d", &x) == 1) {
    addNode(t, x);
  }
  printTree(t);
  freeBT(t);
}
