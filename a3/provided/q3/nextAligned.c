#include <stdio.h>
#include <stddef.h>

void *nextAlignedAddress(void *faddr, size_t size) {
    size_t addr = (size_t)faddr;
    size_t aligned = (addr + size - 1) / size * size;
    return (void *)aligned;
}


int main() {
  void *p;
  if (1 != scanf("%llx", (long long unsigned int *) &p)) {
    printf("Failed to read a hexadecimal number for the pointer!");
    return 1;
  }
  size_t size;
  if (1 != scanf("%lu", &size)) {
    printf("Failed to read an unsigned number for the size!");
    return 1;
  }
  printf("Start of free memory address is: %p\n", p);
  printf("So next %lu size aligned address is: %p\n", size, nextAlignedAddress(p, size));
}
