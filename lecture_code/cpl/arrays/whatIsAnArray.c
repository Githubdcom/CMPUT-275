#include <stdio.h>

int main() {
  int arr[5];
  for (int i = 0; i < 5; ++i) {
    arr[i] = i*2;
  }
  // What is the variable arr? It /is/ an array of integers.
  // That is its type. Clearly it must be, because it size
  // is much larger than an int (its the size of 10 ints)
  printf("Sizeof arr: %lu\n", sizeof arr);
  // But, the index operator is a binary operator that takes
  // two expressions. The way we've called it is with the
  // array as the first operand and an integer as the second
  // operand. So what does the array expression evaluate to then?
  // Since index of would be expr[expr]
  printf("arr: %p\n", arr);
  printf("&arr: %p\n", &arr);
  int *p = &arr;
  printf("Sizeof p: %lu\n", sizeof p);
  printf("p: %p\n", p);
  printf("&p: %p\n", &p);
  // Since an array evaluates to the address of its first item
  // what process does the index of operator actually perform?
  // Note taht our array at this point is {0, 2, 4, 6, 8};
  // Consider the following:
  printf("arr[2]: %d\n", arr[2]);
  printf("*(p+2): %d\n", *(p+2));
  printf("*(arr+2): %d\n", *(arr+2));
  // The index of operator exprA[exprB] is simply shorthand for
  // *(exprA+exprB)
  printf("2[arr]: %d\n", 2[arr]);
  // Due to the semantics of the index of
  // operator simply being the derferencing of the addition of the
  // two operands, and the commutativity of addition the above is
  // /also/ equivalent because *(arr+2) is the same as *(2+arr)
}
