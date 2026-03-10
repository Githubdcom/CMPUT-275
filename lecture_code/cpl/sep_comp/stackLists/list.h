
struct Node;
struct List {
  struct Node *head;
  int len;
};

int length(struct List *);

void initList(struct List *);

struct List *cons(int, struct List *);

void printList(struct List *);

int ith(struct List *, int);

void setIth(struct List *l, int index, int elem);

void removeIth(struct List *l, int i);

struct List * freeList(struct List *l);

int findElem(struct List *l, int elem);

