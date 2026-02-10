#include <stdlib.h>
#include <stdio.h>

int main() {
  int *p = malloc(sizeof(int)*1); // p points at a heap allocated int
  if (!p) {
    // if p is NULL, then malloc failed! React!
    fprintf(stderr, "Malloc failed... I simply can't continue");
    return 1;
  }
  int *arr = malloc(sizeof(int)*10); // arr points at a heap allocated array of 10 ints
  if (!arr) {
    fprintf(stderr, "Malloc failed... I simply can't continue");
  }
  printf("Heap address p points at: %p\n", p);
  printf("Stored there right now (garbage data): %d\n", *p);
  // Remember! Reading unitialized data is undefined behaviour!
  printf("Heap address arr points at: %p\n", arr);
  printf("Initial garbage contents: ");
  for (int i =0; i < 10; ++i) {
    printf("%d ", arr[i]);
    arr[i] = -i; // Initialize now
  }
  printf("\n");
  *p = 13;
  printf("*p new (valid) value: %d\n", *p);
  // I am now done with the data p points at
  free(p); // Free the memory allocated with malloc
  p = NULL; // Suggestion: after freeing memory set that pointer to null
  // That way if you accidentally dereference that pointer your program
  // crashes instead of doing... anything because of undefined behaviour
  printf("New valid array contents: ");
  for (int i =0; i < 10; ++i) {
    printf("%d ", arr[i]);
  }
  printf("\n");
  free(arr);
  arr = NULL;
}
