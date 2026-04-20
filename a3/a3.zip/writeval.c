#include <stdio.h>
#include <string.h>
#include "writeval.h"

static void *nextAlignedAddress(void *faddr, size_t size) {
    size_t addr = (size_t)faddr;
    size_t aligned = (addr + size - 1) / size * size;
    return (void *)aligned;
}

void *writeValue(void *writeLoc, const char *type, void *payload) {
    unsigned char tag;
    void *payloadLoc;
    void *nextFree;

    if (strcmp(type, "int") == 0) {
        tag = 0;
        payloadLoc = nextAlignedAddress(writeLoc + 1, sizeof(int));
        *(unsigned char *)writeLoc = tag;
        *(int *)payloadLoc = *(int *)payload;
        nextFree = payloadLoc + sizeof(int);
    }
    else if (strcmp(type, "char") == 0) {
        tag = 1;
        payloadLoc = writeLoc + 1;
        *(unsigned char *)writeLoc = tag;
        *(char *)payloadLoc = *(char *)payload;
        nextFree = payloadLoc + sizeof(char);
    }
    else if (strcmp(type, "ptr") == 0) {
        tag = 2;
        payloadLoc = nextAlignedAddress(writeLoc + 1, sizeof(void *));
        *(unsigned char *)writeLoc = tag;
        *(void **)payloadLoc = *(void **)payload;
        nextFree = payloadLoc + sizeof(void *);
    }
    else {
        tag = 3;
        payloadLoc = writeLoc + 1;
        *(unsigned char *)writeLoc = tag;
        strcpy((char *)payloadLoc, (char *)payload);
        nextFree = payloadLoc + strlen((char *)payload) + 1;
    }

    return nextFree;
}

void printValues(void *dataStart) {
    void *cur = dataStart;
    int index = 0;

    while (*(unsigned char *)cur != 0xFF) {
        unsigned char tag = *(unsigned char *)cur;

        if (tag == 0) {
            void *payloadLoc = nextAlignedAddress(cur + 1, sizeof(int));
            printf("Value %d at %p: %d\n", index, cur, *(int *)payloadLoc);
            cur = payloadLoc + sizeof(int);
        }
        else if (tag == 1) {
            void *payloadLoc = cur + 1;
            printf("Value %d at %p: '%c'\n", index, cur, *(char *)payloadLoc);
            cur = payloadLoc + sizeof(char);
        }
        else if (tag == 2) {
            void *payloadLoc = nextAlignedAddress(cur + 1, sizeof(void *));
            printf("Value %d at %p: %p\n", index, cur, *(void **)payloadLoc);
            cur = payloadLoc + sizeof(void *);
        }
        else if (tag == 3) {
            void *payloadLoc = cur + 1;
            printf("Value %d at %p: \"%s\"\n", index, cur, (char *)payloadLoc);
            cur = payloadLoc + strlen((char *)payloadLoc) + 1;
        }
        else {
            break;
        }

        index++;
    }
}