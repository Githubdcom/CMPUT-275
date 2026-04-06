#include <sys/mman.h>
#include <stdio.h>
#include "raw.h"
#include <errno.h>

void *getPage(void *start) {
  int *page = mmap(start, PAGESIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, 0, 0);
  if (page == (void *) -1 || page == NULL) {
    fprintf(stderr, "System memory request failed! Irreocoverable\n");
    fprintf(stderr, "Failed with errno %d\n", errno);
    return NULL;
  }
  return page;
}

void *getUserPage() {
  static void *usrStart = (void *) 0x55d653e1500;
  int *page = getPage(usrStart);
  usrStart = usrStart + PAGESIZE;
  return page;
}

void *getSysPage() {
  static void *sysStart = (void *) 0x77d653e1500;
  int *page = getPage(sysStart);
  sysStart = sysStart + PAGESIZE;
  return page;
}


void releasePage(void *page) {
  munmap(page, PAGESIZE);
}
