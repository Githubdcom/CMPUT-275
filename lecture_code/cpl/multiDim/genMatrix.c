#include <stdio.h>
#include <stdlib.h>

int** idMatrix(int n, int m) {
  // We want to generate an array of n rows of  m ints
  // First, allocate our outer array
  int **matrix = malloc(sizeof(int*)*n);
  for (int i = 0; i < n; ++i) {
    int *row = malloc(sizeof(int)*m);
    for (int j = 0; j < m; ++j) row[j] = i==j;
    matrix[i] = row;
  }
  return matrix;
}

int main() {
  int n = 1, m = 1;
  scanf("%d", &n);
  scanf("%d", &m);
  int **mat = idMatrix(n,m);
  for (int i = 0; i < n; ++i) {
    printf("|");
    for (int j = 0; j < m; ++j) {
      printf(" %d", mat[i][j]);
    }
    printf(" |\n");
  }
  for (int i = 0; i < n; ++i) free(mat[i]);
  free(mat);
  mat = NULL;
}
