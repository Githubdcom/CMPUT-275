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
    size_t payloadSize;

    if (strcmp(type, "int") == 0) {
        tag = 0;
        payloadSize = sizeof(int);
    } else if (strcmp(type, "char") == 0) {
        tag = 1;
        payloadSize = sizeof(char);
    } else if (strcmp(type, "ptr") == 0) {
        tag = 2;
        payloadSize = sizeof(void *);
    } else {
        tag = 3;
        payloadSize = strlen((char *)payload) + 1;
    }

    *(unsigned char *)writeLoc = tag;

    void *payloadLoc = nextAlignedAddress(writeLoc + 1, payloadSize);

    if (tag == 0) {
        *(int *)payloadLoc = *(int *)payload;
    } else if (tag == 1) {
        *(char *)payloadLoc = *(char *)payload;
    } else if (tag == 2) {
        *(void **)payloadLoc = *(void **)payload;
    } else {
        strcpy((char *)payloadLoc, (char *)payload);
    }

    return payloadLoc + payloadSize;
}

void printValues(void *dataStart) {
    void *cur = dataStart;

    while (*(unsigned char *)cur != 0xFF) {
        unsigned char tag = *(unsigned char *)cur;

        if (tag == 0) {
            void *payloadLoc = nextAlignedAddress(cur + 1, sizeof(int));
            printf("%d\n", *(int *)payloadLoc);
            cur = payloadLoc + sizeof(int);
        } else if (tag == 1) {
            void *payloadLoc = cur + 1;
            printf("%c\n", *(char *)payloadLoc);
            cur = payloadLoc + sizeof(char);
        } else if (tag == 2) {
            void *payloadLoc = nextAlignedAddress(cur + 1, sizeof(void *));
            printf("%p\n", *(void **)payloadLoc);
            cur = payloadLoc + sizeof(void *);
        } else if (tag == 3) {
            void *payloadLoc = cur + 1;
            printf("%s\n", (char *)payloadLoc);
            cur = payloadLoc + strlen((char *)payloadLoc) + 1;
        } else {
            break;
        }
    }
}