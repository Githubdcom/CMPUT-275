#include <stdio.h>

int main() {
  int cVar = 5;
  cVar = "hello";
  printf("%d\n", cVar);
  printf("%p\n", cVar);
  printf("%s\n", cVar);
}
