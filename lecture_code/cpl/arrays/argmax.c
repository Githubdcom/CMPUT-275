#include <stdio.h>


unsigned int argmax(int arr[], unsigned int len) {
  int *max = arr; // First element is my current max...
  for (int *cur = arr; cur != arr+len; ++cur) {
    if (*cur > *max) max = cur;
  }
  // max is a pointer to the largest item in arr, but I want
  // the /index/ of the largest item.
  return max-arr;
  // When subtracting any two pointers p and z (which point at the same type T)
  // the result of p-z is actually (p-z)/(sizeof(T))
}

unsigned int argmax2(int arr[], unsigned int len) {
  // Assume arr is non-empty
  unsigned int maxInd = 0; // The first item in my array is the largest found
  for (unsigned int i = 0; i < len; ++i) {
    if (arr[i] > arr[maxInd]) {
      // The ith item is larger than the largest I've seen
      // Thus i should become my new max index
      maxInd = i;
    }
  }
  return maxInd;
}

int main() {
  int arr1[] = {77, 33, -2, 500}; // Max is at end
  int arr2[] = {553, 8, 43, 48, 122, 43}; // max is at start
  int arr3[] = {55, 2324, 93, 843, 10, 328, 477};
  printf("argmax of arr1 is %d it should be 3\n", argmax(arr1, 4));
  printf("argmax of arr2 is %d it should be 0\n", argmax(arr2, 6));
  printf("argmax of arr3 is %d it should be 1\n", argmax(arr3, 7));
}
