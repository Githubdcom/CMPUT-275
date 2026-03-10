#include <stdio.h>


int main() {
  int x = 1, y = 2000;
  while (x < y) {
    #ifdef DEBUG
    printf("x is now: %d\n", x);
    printf("y is now: %d\n", y);
    #endif
    x = x*2;
    y = y+50;
  }
}
