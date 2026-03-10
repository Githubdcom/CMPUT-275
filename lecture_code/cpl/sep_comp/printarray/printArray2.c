#include <stdio.h>

void printArray(int *arr, int len, char end) {
  if (len == 0) {
    printf("{}");
    return;
  }
  printf("{%d", arr[0]);
  for (int i = 1; i < len; ++i) {
    printf(", %d", arr[i]);
  }
  printf("}");
  if (end) {
    printf("%c", end);
  }
}
