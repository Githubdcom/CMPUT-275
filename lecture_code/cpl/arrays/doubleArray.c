#include <stdio.h>

void doubleArray(int arr[], unsigned int size) {
  for (unsigned int i = 0; i < size; ++i) {
    arr[i] = arr[i]*2;
  }
}

int main() {
  int arr[5] = {1, 2, 3, 4, 5};
  doubleArray(arr, 5);
  for (unsigned int i = 0; i < 5; ++i) {
    printf("%d\n", arr[i]);
  }
}
