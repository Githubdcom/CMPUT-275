#include <stdio.h>
#include <stdlib.h>

struct IntArray {
  int *arr;
  int len;
  int cap;
};

void append(struct IntArray *p, int v) {
  /*
  * append adds the given value v to the back of the
  *        array arr, growing it if necessary
  * arr - ptr to the start of the array
  * len - number of items currently stored in the array
  * cap - maximum number of items there is space for in the array
  * v   - the new value to add
  *
  * returns - nothing
  * Side Effects:
  *    mutates arr
  */
  if (p->cap == p->len) { // Array is full!
    int *newArr = malloc(sizeof(int)*(p->cap*2));
    for (int i = 0; i < p->len; ++i) newArr[i] = p->arr[i];
    // I have now copied everything...
    // make newArr /be/ my array.
    free(p->arr);
    p->arr = newArr;
    p->cap = p->cap*2;
  }
  p->arr[p->len++] = v;
}

void pop(struct IntArray *p) {
  --p->len;
}

int main() {
  struct IntArray ia;
  ia.cap = 4;
  ia.arr = malloc(sizeof(int)*ia.cap);
  ia.len = 0;
  while (!feof(stdin)) {
    int x = 0;
    int rc = scanf("%d", &x);
    if (rc == 1) append(&ia, x);
  }
  pop(&ia);
  append(&ia, 222);
  for (int i = 0; i < ia.len-1; ++i) {
    printf("%d ", ia.arr[i]);
  }
  printf("%d", ia.arr[ia.len-1]);
  printf("\n");
  free(ia.arr);
  ia.arr = NULL;
}
