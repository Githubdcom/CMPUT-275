#include <stdio.h>

#define SIZE 100
int main() {
  int arr[SIZE];
  for (int i = 0; i < SIZE; ++i) {
    arr[i] = (i-1)*-1;
    printf("%d\n", arr[i]);
  }
}
