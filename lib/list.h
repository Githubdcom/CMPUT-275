
struct List;

int length(struct List *);

struct List *empty();

struct List *cons(int, struct List *);

void printList(struct List *);

int ith(struct List *, int);

void setIth(struct List *l, int index, int elem);

void removeIth(struct List *l, int i);

struct List *freeList(struct List *l);

int findElem(struct List *l, int elem);

void sort(struct List *l, int (*cmp)(int, int));
