#include <stdio.h>

void printArray(int *par, int len) {
  for (unsigned int i = 0; i < len; ++i) {
    printf("%d ", par[i]);
  }
  printf("\n");
}

int main() {
  int arr[] = {23, 5489, 5310, 33, 32, 11, 11, 334, 67, 1};
  printArray(arr, sizeof arr/sizeof arr[0]);
  printArray(arr+2, (sizeof arr/sizeof arr[0])-2);
}
