#include <stdio.h>
#include "raw.h"
#include <string.h>
#include "writeval.h"

int main() {
  // We could just put this on the stack, but then the memory addresses would be random.
  // We instead use the provided raw module to ensure we get access to exactly the same
  // memory addresses each executon so output can always match for our testcases.
  // Use of this process for allocating memory may mean this does not compile on your
  // computer, and you will have to test on Ohaton.
  void *freeStart = getUserPage();
  // Allocate another block right after
  // freeStart, so we have 2*PAGESIZE bytes free starting
  // at freeStart. While we store secondBlock for printing,
  // we could choose not to store it and note that we have
  // PAGESIZE*2 bytes allocated starting at freeStart.
  void *secondBlock = getUserPage();
  // Initialize all bits in allocated memory to on, so that
  // printValues has some meaning of uninitialized memory.
  for (int i = 0; i < (PAGESIZE*2)/sizeof(int); ++i) {
    ((int*)(freeStart))[i] = -1;
  }
  void *origin = freeStart;
  char buff[256];
  int printVals = 1;
  printf("The beginning of allocated memory is %p\n", freeStart);
  printf("Second block is exactly %d bytes ahead of first block at %p\n", PAGESIZE, secondBlock);
  printf("The end of allocated memory is %p\n", freeStart+PAGESIZE*2);
  while (scanf("%255s", buff) == 1) {
    if (freeStart >= origin + PAGESIZE*2 - 1) {
      printf("Ran out of memory, test case too large!");
      printVals = 0;
      break;
    }
    if (strcmp(buff, "int") == 0) {
      int x = 0;
      if (scanf("%d", &x) != 1) {
        printf("Expected integer after int, did not receive that.");
        break;
      }
      freeStart = writeValue(freeStart, buff, &x);
    }
    else if (strcmp(buff, "char") == 0) {
      char c = 0;
      if (scanf(" %c", &c) != 1) {
        printf("Expected character after char, did not receive that.");
        break;
      }
      freeStart = writeValue(freeStart, buff, &c);
    }
    else if (strcmp(buff, "ptr") == 0) {
      void *p = 0;
      if (scanf("%llx", (long long unsigned int *)&p) != 1) {
        printf("Expected a hexadecimal number (without preceding 0x) after ptr, did not receive that.");
                break;
      }
      freeStart = writeValue(freeStart, buff, &p);
    }
    else if (strcmp(buff, "str") == 0) {
      char sbuff[1024];
      if (scanf("%1023s", sbuff) != 1) {
        printf("Expected a string after str, did not receive that.");
        break;
      }
      freeStart = writeValue(freeStart, buff, sbuff);
    }
    else {
      printf("Received invalid value type \"%s\", something is wrong with this test case.\n", buff);
    }
  }
  if (printVals) {
    printf("Done reading in data, now printing out everything read in.\n");
    printValues(origin);
  }
}
