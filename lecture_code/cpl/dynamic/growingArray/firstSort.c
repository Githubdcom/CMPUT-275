#include <stdio.h>

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
  #define CAPACITY 10
  int arr[CAPACITY];
  int len = 0;
  while (!feof(stdin)) {
    int x = 0;
    int rc = scanf("%d", &x);
    if (rc == 1) {
      insert(arr, len, CAPACITY, x);
      ++len;
    }
  }
  for (int i = 0; i < len; ++i) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}
