#include <stdio.h>
#include <string.h>
int main() {
  char myS[] = {'a', 'b', 'c'}; // myS is /NOT/ a string! It doesn't include a null terminator
  char s[] = {'x', 'y', 'z', '\0', 't', 'p'}; // s is a string it does include a null terminator
  printf("address of myS: %p\n", myS);
  printf("address of s: %p\n", s);
  printf("strlen(s): %lu\n", strlen(s));
  printf("strlen(myS): %lu\n", strlen(myS));
  printf("s: '%s'\n", s);
  printf("myS: '%s'\n", myS);
}
