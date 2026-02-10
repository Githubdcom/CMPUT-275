#include <stdio.h>

int main() {
  int x = 0;
  long long int y = 10;
  printf("size of int: %ld\n", sizeof(int));
  printf("Size of long long int: %ld\n", sizeof(long long int));
  int *p = &x;
  long long int *z = &y;
  printf("Size of a int *: %ld\n", sizeof(int*));
  printf("Size of a long long int *: %ld\n", sizeof(long long int*));

  printf("Value of p: %p\n", p);
  printf("Value of z: %p\n", z);
  ++p;
  ++z;
  printf("Value of p after incrementing: %p\n", p);
  printf("Value of z after incrementing: %p\n", z);
  /*
  * What is occurring here is called /pointer arithmetic/ which is
  * simply to say when an integer x is added to a pointer p the result
  * is not simply x+p as it would be if they were treated as integers
  * it is instead p + x*sizeof(*p)
  */
}
