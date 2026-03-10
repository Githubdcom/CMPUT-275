#include "list.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
struct List {
  int *arr;
  int len;
  int cap;
};

int length(struct List *l) {
  return l->len;
}

struct List *empty() {
  struct List *l = malloc(sizeof(struct List));
  l->arr = malloc(4*sizeof(int));
  l->len = 0;
  l->cap = 4;
  return l;
}

struct List *cons(int elem, struct List *l) {
  // We will push this element to the back of our array
  // in our implementation the front of the list is stored
  // at element len-1 of our array. The end of the list is
  // stored at index 0
  if (l->len == l->cap) {
    int *newArr = malloc(l->cap*2*sizeof(int));
    for (int i = 0; i < l->len; ++i) {
      newArr[i] = l->arr[i];
    }
    free(l->arr);
    l->arr = newArr;
    l->cap = l->cap*2;
  }
  l->arr[l->len++] = elem;
}

void printList(struct List *l) {
  if (l->len == 0) {
    printf("[]");
    return;
  }
  printf("[%d", l->arr[l->len - 1]);
  // CAREFUL if you use a unsigned integer i
  for (int i = l->len-2; i >= 0; --i) {
    printf(", %d", l->arr[i]);
  }
  printf("]");
}

int ith(struct List *l, int i) {
  // Since our List is stored in reverse order in
  // our array, the ith element of our list is:
  // if i is zero, then len-1-0
  // if i is 1, then len-1-1
  // if i is 2, then len-1-2
  // so len-1-i
  assert(i < l->len);
  return l->arr[l->len-1-i];
}

void setIth(struct List *l, int i, int elem) {
  assert(i < l->len);
  l->arr[l->len-1-i] = elem;
}

void removeIth(struct List *l, int i) {
  assert(i < l->len);
  i = l->len - 1 - i;
  for (int j = i; j < l->len-1; ++j) {
    l->arr[j] = l->arr[j+1];
  }
  --l->len;
}

struct List * freeList(struct List *l) {
  free(l->arr);
  free(l);
}

int findElem(struct List *l, int elem) {
  for (int i = 0; i < l->len; ++i) {
    if (l->arr[i] == elem) {
      return l->len - 1 - i;
    }
  }
  return -1;
}

void merge(int *arr, int ls, int le, int rs, int re, int (*cmp)(int,int)) {
  // NOT IN PLACE! Challenge question: Solve this without using
  // an extra array
  // Assumption: le=rs
  assert(le == rs);
  int *temp = malloc(sizeof(int)*(re-ls));
  int *tmploc = temp;
  int leftInd = ls;
  int rightInd = rs;
  while (leftInd < le && rightInd < re) {
    if (!cmp(arr[leftInd], arr[rightInd])) {
      *tmploc = arr[leftInd];
      ++tmploc;
      ++leftInd;
    } else {
      *tmploc = arr[rightInd];
      ++tmploc;
      ++rightInd;
    }
  }
  for (; leftInd < le; ++leftInd, ++tmploc) *tmploc = arr[leftInd];
  for (; rightInd < re; ++rightInd, ++tmploc) *tmploc = arr[rightInd];
  // Again, we are assuming our precondtion that le was rs, so these are contiguous
  tmploc = temp;
  for (int i = ls; i < re; ++i, ++tmploc) {
    arr[i] = *tmploc;
  }
  free(temp);
}

void mergeSort(int *arr, int start, int end, int (*cmp)(int,int)) {
  int len = end-start;
  if (len <= 1) return; // A 0 or 1 length array is trivially sorted
  int offset = len/2;
  int rightStart, leftEnd, leftStart, rightEnd;
  rightStart = leftEnd = start + len/2;
  leftStart = start;
  rightEnd = end;
  mergeSort(arr, leftStart, leftEnd, cmp);
  mergeSort(arr, rightStart, rightEnd, cmp);
  merge(arr, leftStart, leftEnd, rightStart, rightEnd, cmp);
}

void sort(struct List *l, int (*cmp)(int, int)) {
  mergeSort(l->arr, 0, l->len, cmp);
}
