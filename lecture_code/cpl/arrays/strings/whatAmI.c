#include <stdio.h>
#include <string.h>
int whatAmI(const char *s) {
  for (const char *end = strlen(s) + s - 1; s < end; ++s, --end) {
    if (*end != *s) return 0;
  }
  return 1;
}

int main() {
  const char *p = "amanaplanacanalpanama";
  const char *s = "hello";
  printf("'%s' %s a palindrome\n", p, whatAmI(p) ? "is" : "is not");
  printf("'%s' %s a palindrome\n", s, whatAmI(s) ? "is" : "is not");
}
