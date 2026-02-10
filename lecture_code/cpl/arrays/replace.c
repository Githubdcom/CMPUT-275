#include <stdio.h>

unsigned int replace(int arr[], unsigned int len, int tar, int repl) {
  // replaces each occurrence of tar in arr with repl
  // and returns the number of items replaced
  unsigned int cnt = 0;
  for (int *end = arr+len; arr != end; ++arr) {
    if (*arr == tar) {
      *arr = repl;
      ++cnt;
    }
  }
  return cnt;
}

void printArr(int arr[], unsigned int len) {
  if (len == 0) return;
  for (unsigned int i = 0; i < len-1; ++i) {
    printf("%d ", arr[i]);
  }
  printf("%d", arr[len-1]);
}

int main() {
  int arr[] = {1, 6, 1, 4, 3, 9, 1};
  unsigned int len = 7;
  printf("Array originally: ");
  printArr(arr, len);
  printf("\n");
  replace(arr, len, 1, 5);
  printf("Array after replacing 1 with 5: ");
  printArr(arr, len);
  printf("\n");
}
