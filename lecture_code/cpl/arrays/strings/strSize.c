#include <stdio.h>
#include <string.h>
int main() {
  char s[] = "abcd";
  char same[] = {'a', 'b', 'c', 'd', '\0'};
  printf("strlen(s): %lu\n", strlen(s));
  printf("Size of s: %lu\n", sizeof s);
}
