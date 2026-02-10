#include <stdio.h>
#include <stdlib.h>
const char *mystrchr(const char *s, const char c) {
  // Returns a pointer to the first occurrence of the character c if
  // the character c exists in the string s, otherwise returns NULL
  while (*s) {
    if (*s == c) return s;
    ++s;
  }
  return NULL;
}


int main() {
  char sArr[] = "hello";
  const char *eLoc = mystrchr(sArr, 'e'); // Here returned pointer lives on the stack
  char *hArr = malloc(sizeof(char)*5);
  hArr[0] = 'a'; hArr[1] = 'b'; hArr[2] = 'c'; hArr[3] = 'd'; hArr[4] ='\0';
  const char *bLoc = mystrchr(hArr, 'b'); // Here the returned pointer lives on the heap
  const char *s = "Yet another string";
  const char *rLoc = mystrchr(s, 'r');
  printf("eLoc: %p\nbLoc: %p\nrLoc: %p\n", eLoc, bLoc, rLoc); // Here the return pointer lives on data segment (technically could be text as well)
  free(hArr);
}
