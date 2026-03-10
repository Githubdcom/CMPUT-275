#include <stdio.h>

int main(int argc, char **argv) {
  char **s = argv;
  while (*s) {
    printf("Argument %d: %s\n", s-argv, *s);
    ++s;
  }
}
