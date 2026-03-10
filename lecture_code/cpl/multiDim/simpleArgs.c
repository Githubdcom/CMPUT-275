#include <stdio.h>

int main(int argc, char *argv[]) {
  printf("Received %d arguments\n", argc);
  for (int i = 0; i < argc; ++i) {
    printf("Arg %d: %s\n", i, argv[i]);
  }
}
