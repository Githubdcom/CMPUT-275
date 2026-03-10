
struct BTImpl;

struct BTree {
  struct BTImpl *pimpl;
};

struct BTree *empty();

void addNode(struct BTree *bt, int elem);

void printTree(struct BTree *bt);

void freeBT(struct BTree *bt);

int contains(struct BTree *bt, int elem);
