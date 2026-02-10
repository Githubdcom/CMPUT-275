#include <stdio.h>

int cmps(const char *s1, const char *s2) {
  // returns 1 if s1 > s2
  // returns 0 if s1 == s2
  // returns -1 if s1 < s2
  while (*s1 && *s2 && *s1 == *s2) {
    ++s1; ++s2;
  }
  // if they are equal, return 0
  if (*s1 == *s2) return 0;
  // if s1 is less than return -1
  if (*s1 < *s2) return -1;
  return 1;
}

int main() {
  char buf2[256];
  char buf1[256];
  scanf("%255s", buf1);
  scanf("%255s", buf2);
  // Note... buf1 and buf2 are arrays.
  // That means when used as expressions they evaluate to the address of the first item
  // so buf1 < buf2 simply compares the addresses of these arrays... nothing about their
  // contents!
  if (buf1 < buf2) {
    printf("'%s' is less than '%s'\n", buf1, buf2);
  } else if (buf1 > buf2) {
    printf("'%s' is greater than '%s'\n", buf1, buf2);
  } else {
    printf("'%s' is equal to '%s'\n", buf1, buf2);

  }
  // If we want to compare strings lexicographically we must iterate over the
  // strings looking for a difference
  int res = cmps(buf1, buf2);
  if (res < 0) {
    printf("'%s' is less than '%s'\n", buf1, buf2);
  } else if (res > 0) {
    printf("'%s' is greater than '%s'\n", buf1, buf2);
  } else {
    printf("'%s' is equal to '%s'\n", buf1, buf2);
  }
}
