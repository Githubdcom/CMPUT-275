#include <stdio.h>


int main() {
  char buff[16];
  // Much safer, if you're going to use scanf, to specify the maximum number of
  // chars read in so you don't go past the end of your array.
  // however, this means if the user types a string larger than your buffer size
  // it will get broken up over multiple reads.
  while (scanf("%15s", buff) == 1) {
    printf("The string read in was: %s\n", buff);
  }
  // if we actually want to be able to read an arbitrary length string we
  // need another solution... we must solve the problem ourselves creating
  // our own ADT.
}
