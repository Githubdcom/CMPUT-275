#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
struct BTNode {
  // If left or right is NULL it means
  // we do not have a chld there.
  // otherwise they are a node representing a subtree
  int data;
  struct BTNode *left;
  struct BTNode *right;
};

struct BTImpl {
  struct BTNode *root;
};


struct BTree *empty() {
  struct BTImpl *impl = malloc(sizeof(struct BTImpl));
  impl->root = NULL;
  // a NULL root is the empty tree
  struct BTree *bt = malloc(sizeof(struct BTree));
  bt->pimpl = impl;
}

struct BTNode *insert2(struct BTNode *bt, int n) {
  // Returns the Node that was asked.
  // Which is either bt itself (after having updated it)
  // or the newly created node
  if (!bt) {
    struct BTNode *newNode = malloc(sizeof(struct BTNode));
    newNode->right = newNode->left = NULL;
    newNode->data = n;
    return newNode;
  } else {
    if (n < bt->data) {
      bt->left = insert2(bt->left, n);
    } else {
      bt->right = insert2(bt->right, n);
    }
    return bt;
  }
}

void insert(struct BTNode *bt, int n) {
  // Assuming n does not already exist in the bt!
  if (n < bt->data) {
    // Two possibilities left is NULL or its a subtree
    if (bt->left) {
      insert(bt->left, n);
    } else {
      // If left is NULL we must become this nodes left child!
      struct BTNode *newNode = malloc(sizeof(struct BTNode));
      newNode->data = n;
      newNode->left = NULL;
      newNode->right = NULL;
      bt->left = newNode;
    }
  } else {
    // Otherwise we are bigger
    // Two possibilities left is NULL or its a subtree
    if (bt->right) {
      insert(bt->right, n);
    } else {
      // If left is NULL we must become this nodes left child!
      struct BTNode *newNode = malloc(sizeof(struct BTNode));
      newNode->data = n;
      newNode->left = NULL;
      newNode->right = NULL;
      bt->right = newNode;
    }
  }
}

void addNode(struct BTree *bt, int elem) {
  if (NULL == bt->pimpl->root) {
    struct BTNode *newNode = malloc(sizeof(struct BTNode));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->data = elem;
    bt->pimpl->root = newNode;
    return;
  }
  insert(bt->pimpl->root, elem);
}

void printNode(struct BTNode *bt, int indentLevel) {
  for (int i = 0; i < indentLevel; ++i) {
    printf("\t");
  }
  if (bt) {
    printf("| %d\n", bt->data);
    printNode(bt->left, indentLevel+1);
    printNode(bt->right, indentLevel+1);
  } else {
    printf("|\n");
  }
}

void printTree(struct BTree *bt) {
  printNode(bt->pimpl->root, 0);
}

void freeNode(struct BTNode *bt) {
  if (bt) {
    freeNode(bt->left);
    freeNode(bt->right);
    free(bt);
  }
}

void freeBT(struct BTree *bt) {
  freeNode(bt->pimpl->root);
  free(bt->pimpl);
  free(bt);
}


int nodeContains(struct BTNode *node, int elem) {
  if (!node) return 0;
  if (node->data == elem) return 1;
  if (elem < node->data) return nodeContains(node->left, elem);
  if (elem > node->data) return nodeContains(node->right, elem);
}

int contains(struct BTree *bt, int elem) {
  // returns 0 if elem does not exist in bt, 1 if it does
  return nodeContains(bt->pimpl->root, elem);
}
