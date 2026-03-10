void printArray(int *, int, char);

int main() {
  int arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  printArray(arr, sizeof(arr)/sizeof(arr[0]), '\n');
}
