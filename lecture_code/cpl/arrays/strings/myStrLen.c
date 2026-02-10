#include <stdio.h>

long unsigned int ourstrlen(const char *p) {
  // returns the length of the string p points at
  // p must point at a valid c_str
  long unsigned int len = 0;
  for (; *p; ++p, ++len);
  return len;
}

int main() {
  const char *p = "abcd";
  printf("ourstrlen(p): %lu\n", ourstrlen(p));
  char myArr[] = "this is another string";
  printf("ourstrlen(myArr): %lu\n", ourstrlen(myArr));
}
