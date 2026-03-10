#include <stdio.h>

int main(int argc, int *argv[]) {
  int matrix[3][4];
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      matrix[i][j] = i*j;
    }
  }
  int r1[4] = {5, 6, 7, -1};
  int r2[4] = {8, 9, 10, -1};
  int r3[4] = {11, 12, 13, -1};
  int *matPtr[3] = {r1, r2, r3};
  // matrix is a 3x4 2d array of integers.
  // Which is it to say it's an array of 3 arrays.
  // It is important that this is /NOT/ an array of pointers
  // (which is the common way we'll implement 2d arrays)
  // this is /ACTUALLY/ an array of arrays!
  printf("sizeof matrix: %lu\n", sizeof(matrix));
  printf("sizeof matptr: %lu\n", sizeof(matPtr));
  // argv is a pointer to an array of pointers to arrays of characters
  // We us argv to implement a two dimensional array (an array of strings, strings
  // themselves being arrays) but semantically these two things are different
  printf("sizeof argv: %lu\n", sizeof(argv));

  printf("sizeof matrix[0]: %lu\n", sizeof(matrix[0]));
  printf("sizeof argv[0]: %lu\n", sizeof(argv[0]));
  printf("sizeof matPtr[0]: %lu\n", sizeof(matPtr[0]));

  printf("expr matrix: %p\n", matrix);
  printf("expr matrix[0]: %p\n", matrix[0]);
  printf("expr matrix[1]: %p\n", matrix[1]);
  printf("expr matrix[2]: %p\n", matrix[2]);
}
