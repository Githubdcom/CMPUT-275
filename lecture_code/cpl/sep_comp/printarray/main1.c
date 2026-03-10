

void printArray(int *, int, char);
extern char defaultEnd;
int main() {
  int arr[] = {1, 2, 3, 4};
  printArray(arr, sizeof(arr)/sizeof(arr[0]), defaultEnd);
}
