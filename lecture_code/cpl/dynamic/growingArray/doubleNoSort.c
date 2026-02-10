#include <stdio.h>
#include <stdlib.h>

int insert(int *arr, const int len, const int cap, const int nv) {
  if (cap <= len) return 0;
  // Inserts nv into arr in sorted order
  int i = 0;
  for (; i < len && arr[i] < nv; ++i);
  for (int j = len; j > i; --j) {
    arr[j] = arr[j-1];
  }
  arr[i] = nv;
  return 1;
}

int main() {
  int cap = 16;
  int *arr = malloc(sizeof(int)*cap);
  int len = 0;
  while (!feof(stdin)) {
    int x = 0;
    int rc = scanf("%d", &x);
    if (rc == 1) {
      if (cap == len) { // Array is full!
        int *newArr = malloc(sizeof(int)*(cap*2));
        // We should always check if malloc fails!
        for (int i = 0; i < len; ++i) newArr[i] = arr[i];
        // I have now copied everything...
        // make newArr /be/ my array.
        free(arr);
        arr = newArr;
        cap = cap*2;
      }
      arr[len++] = x; // Don't sort, just append
    }
  }
  for (int i = 0; i < len; ++i) {
    printf("%d ", arr[i]);
  }
  printf("\n");
  free(arr);
  arr = NULL;
}
