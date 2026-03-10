#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
struct Node {
  int data;
  struct Node *next;
};

struct List {
  struct Node *head;
  int len;
};

int length(struct List *);

void initList(struct List *l) {
  l->len = 0;
  l->head = NULL;
}

struct List *cons(int elem, struct List *l) {
  struct Node *nn = malloc(sizeof(struct Node));
  // should be checking malloc didn't return NULL;
  nn->next = l->head;
  nn->data = elem;
  l->head = nn;
  l->len++;
  return l;
}

void printList(struct List *l) {
  if (l->head == NULL) {
    printf("[]");
    return;
  }
  printf("[");
  struct Node *cur = l->head;
  printf("%d", cur->data);
  for (cur=cur->next; cur; cur=cur->next) {
    printf(", %d", cur->data);
  }
  printf("]");
}

int ith(struct List *l, int i) {
  assert(i < length(l));
  struct Node *cur = l->head;
  for (int j = 0; cur && j < i; ++j, cur = cur->next);
  return cur->data;
}

void setIth(struct List *l, int i, int elem) {
  assert(i < length(l));
  struct Node *cur = l->head;
  for (int j = 0; cur && j < i; ++j, cur = cur->next);
  cur->data = elem;
}

void removeIth(struct List *l, int i) {
  assert(i < length(l));
  struct Node *cur = l->head;
  for (int j = 0; cur && j < i-1; ++j, cur=cur->next);
  // After this loop cur points at the node /before/ the one we
  // want to remove
  struct Node *toRemove = cur->next;
  cur->next = cur->next->next;
  free(toRemove);
}

int length(struct List *l) {
  return l->len;
}

void freeNode(struct Node *n) {
  if (!n) return; // base case, do nothing. n is NULL
  freeNode(n->next);
  free(n);
}

struct List * freeList(struct List *l) {
  freeNode(l->head);
  return NULL;
}

int findElem(struct List *l, int elem) {
  // returns the first index of elem in l
  // or -1 if not found
  int i = 0;
  for (struct Node *cur=l->head; cur; cur=cur->next, ++i) {
    if (cur->data == elem) return i;
  }
  return -1;
}

