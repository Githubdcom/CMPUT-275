#include "list.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
struct listImpl {
  int *arr;
  int len;
  int cap;
};

int length(struct List *l) {
  return l->pimpl->len;
}

void initList(struct List *l) {
  struct listImpl *li = malloc(sizeof(struct listImpl));
  li->arr = malloc(4*sizeof(int));
  li->len = 0;
  li->cap = 4;
  l->pimpl = li;
}

struct List *cons(int elem, struct List *l) {
  // We will push this element to the back of our array
  // in our implementation the front of the list is stored
  // at element len-1 of our array. The end of the list is
  // stored at index 0
  if (l->pimpl->len == l->pimpl->cap) {
    int *newArr = malloc(l->pimpl->cap*2*sizeof(int));
    for (int i = 0; i < l->pimpl->len; ++i) {
      newArr[i] = l->pimpl->arr[i];
    }
    free(l->pimpl->arr);
    l->pimpl->arr = newArr;
    l->pimpl->cap = l->pimpl->cap*2;
  }
  l->pimpl->arr[l->pimpl->len++] = elem;
  return l;
}

void printList(struct List *l) {
  if (l->pimpl->len == 0) {
    printf("[]");
    return;
  }
  printf("[%d", l->pimpl->arr[l->pimpl->len - 1]);
  // CAREFUL if you use a unsigned integer i
  for (int i = l->pimpl->len-2; i >= 0; --i) {
    printf(", %d", l->pimpl->arr[i]);
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
  assert(i < l->pimpl->len);
  return l->pimpl->arr[l->pimpl->len-1-i];
}

void setIth(struct List *l, int i, int elem) {
  assert(i < l->pimpl->len);
  l->pimpl->arr[l->pimpl->len-1-i] = elem;
}

void removeIth(struct List *l, int i) {
  assert(i < l->pimpl->len);
  i = l->pimpl->len - 1 - i;
  for (int j = i; j < l->pimpl->len-1; ++j) {
    l->pimpl->arr[j] = l->pimpl->arr[j+1];
  }
  --l->pimpl->len;
}

struct List * freeList(struct List *l) {
  free(l->pimpl->arr);
  free(l->pimpl);
  return NULL;
}

int findElem(struct List *l, int elem) {
  for (int i = 0; i < l->pimpl->len; ++i) {
    if (l->pimpl->arr[i] == elem) {
      return l->pimpl->len - 1 - i;
    }
  }
  return -1;
}

