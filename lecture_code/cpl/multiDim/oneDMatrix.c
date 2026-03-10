#include <stdio.h>
#include <stdlib.h>

int pow10(unsigned int e) {
  int ret = 1;
  while (e > 0) {
    ret = ret*10;
    --e;
  }
  return ret;
}

int *genMatrix(int n, int m) {
  // Generates the n*m matrix that
  // has the elemnts 1*10^rownum...m*10^rownum in each row
  // by rows.
  // Returns a 1D matrix that represents
  // a row-order storage of the matrix
  // e.g. a 3x3 matrix with this should be
  // | 1   2   3   |
  // | 10  20  30  |
  // | 100 200 300 |
  int *mat = malloc(sizeof(int)*n*m);
  for (int i = 0; i < n*m; ++i) {
    int rowNum = i/m;
    int colNum = i%m;
    mat[i] = pow10(rowNum)*colNum;
  }
  return mat;
}

int getValue(int *mat, int r, int c, int nc) {
  return mat[r*nc+c];
}

void printRC(int *mat, int i, int nr, int nc) {
  // Given an index i into the matrix mat
  // print out the corresponding coordiante (r,c)
  printf("(%d, %d)", i/nc, i%nc);
}

int main() {
  int r=1,c=1;
  scanf("%d", &r);
  scanf("%d", &c);
  int *mat = genMatrix(r, c);
  for (int i = 0; i < r; ++i) {
    printf("| ");
    for (int j = 0; j < c; ++j) {
      printf("%d ", mat[i*c+j]);
    }
    printf("|\n");
  }
  for (int i = 0; i < r*c; ++i) {
    printf("index %d maps to ", i);
    printRC(mat, i, r, c);
    printf("\n");
  }
  free(mat);
}
