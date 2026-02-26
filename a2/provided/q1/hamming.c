#include <stdio.h>
#include <stdlib.h>

static unsigned int parse_u32(const char *s) {
    /* Input guaranteed valid per assignment; strtoul handles range well. */
    return (unsigned int)strtoul(s, NULL, 10);
}

int main(int argc, char **argv) {
    if (argc != 4) {
        return 1;
    }

    unsigned int a = parse_u32(argv[1]);
    unsigned int b = parse_u32(argv[2]);
    unsigned int base = parse_u32(argv[3]);

    /* base is guaranteed > 1 by spec */
    unsigned int dist = 0;

    /* Treat 0 as a one-digit representation "0" */
    if (a == 0 && b == 0) {
        printf("0\n");
        return 0;
    }

    while (a != 0 || b != 0) {
        unsigned int da = (a != 0) ? (a % base) : (unsigned int)(base + 1); /* sentinel */
        unsigned int db = (b != 0) ? (b % base) : (unsigned int)(base + 1);

        if (da != db) {
            dist++;
        }

        if (a != 0) a /= base;
        if (b != 0) b /= base;
    }

    printf("%u\n", dist);
    return 0;
}