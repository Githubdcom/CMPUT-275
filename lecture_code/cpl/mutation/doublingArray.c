#include <stdio.h>
#include <stdlib.h>

void append(int **arr, int *len, int *cap, int v) {
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
  if (*cap == *len) { // Array is full!
    int *newArr = malloc(sizeof(int)*(*cap*2));
    for (int i = 0; i < *len; ++i) newArr[i] = (*arr)[i];
    // I have now copied everything...
    // make newArr /be/ my array.
    free(*arr);
    *arr = newArr;
    *cap = *cap*2;
  }
  (*arr)[(*len)++] = v;
}

void pop(int **arr, int *len, int *cap) {
  --*len;
}

int main() {
  int cap = 4;
  int *arr = malloc(sizeof(int)*cap);
  int len = 0;
  while (!feof(stdin)) {
    int x = 0;
    int rc = scanf("%d", &x);
    if (rc == 1) append(&arr, &len, &cap, x);
  }
  pop(&arr, &len, &cap);
  append(&arr, &len, &cap, 222);
  for (int i = 0; i < len-1; ++i) {
    printf("%d ", arr[i]);
  }
  printf("%d", arr[len-1]);
  printf("\n");
  free(arr);
  arr = NULL;
}
