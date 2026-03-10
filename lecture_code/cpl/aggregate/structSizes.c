#include <stdio.h>

struct Foo {
  int x, y;
};

struct Bar {
  int x, y;
  char a;
};

struct T {
  int x, y;
  char a;
  int z;
  char b, c, d;
};

struct Q {
  int x, y;
  char a, b, c, d;
  int z;
};


int main() {
  struct Foo f;
  printf("Size of Foo type: %lu\n", sizeof(f));
  struct Bar b;
  printf("Size of Bar type: %lu\n", sizeof(b));
  printf("Size of T type: %lu\n", sizeof(struct T));
  printf("Size of Q type: %lu\n", sizeof(struct Q));
}

