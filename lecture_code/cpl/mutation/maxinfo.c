#include <stdio.h>
#include <assert.h>

float maxInfo(float *arr, int len, int *indLoc) {
  assert(len > 0);
  int maxInd = 0;
  float maxVal = arr[0];
  for (int i = 1; i < len; ++i) {
    if (arr[i] > arr[maxInd]) {
      maxInd = i;
      maxVal = arr[i];
    }
  }
  *indLoc = maxInd;
  return maxVal;
}

int main() {
  float arr[] = {242.3, 4884.3, 20193.2, -1292.2, 2123213.33};
  int maxInd = 0;
  float max = maxInfo(arr, sizeof(arr)/sizeof(arr[0]), &maxInd);
  printf("The max value of the array is %f and its index is %d\n", max, maxInd);
}
