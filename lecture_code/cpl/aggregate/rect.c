#include <stdio.h>
#include <stdlib.h>

struct Rect {
  int x, y, w, h;
  char c;
};

int collides(struct Rect r1, struct Rect r2) {
  return (r1.x < r2.x + r2.w &&
          r1.x + r1.w > r2.x &&
          r1.y < r2.y + r2.h &&
          r1.y + r1.h > r2.y);
}

void translate(struct Rect *r, int xt, int yt) {
  r->x += xt;
  r->y += yt;
}

void printGrid(int xDim, int yDim, struct Rect *arr, int len) {
  for (int i = 0; i < yDim; ++i) {
    for (int j = 0; j < xDim; ++j) {
      int foundRect = 0;
      struct Rect unitRect = {.x=j, .y=i, .w=1, .h=1, .c='*'};
      for (int r = 0; r < len; ++r) {
        if (collides(arr[r], unitRect)) {
          foundRect = 1;
          printf("%c", arr[r].c);
          break;
        }
      }
      if (!foundRect) printf("*");
    }
    printf("\n");
  }
}

int main(int argc, char **argv) {
  struct Rect r1;
  r1.x = 1;
  r1.y = 2;
  r1.w = 3;
  r1.h = 2;
  r1.c = '^';
  printf("%lu\n", sizeof(r1));
  int xDim = atoi(argv[1]);
  int yDim = atoi(argv[2]);
  struct Rect r2;
  r2.x=3;
  r2.y=3;
  r2.w=2;
  r2.h=2;
  r2.c='&';
  struct Rect arr[] = {r1, r2};
  printGrid(xDim, yDim, arr, sizeof(arr)/sizeof(arr[0]));
  translate(arr+1, 2, 0);
  printf("Printing grid second time:\n");
  printGrid(xDim, yDim, arr, sizeof(arr)/sizeof(arr[0]));

}
