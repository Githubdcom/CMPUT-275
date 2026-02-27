#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *data;          /* not NUL-terminated */
    unsigned int len;
    unsigned int cap;
} SString;

static void s_init(SString *s) {
    s->cap = 4;
    s->len = 0;
    s->data = (char *)malloc(s->cap);
    if (s->data == NULL) {
        exit(1);
    }
}

static void s_free(SString *s) {
    free(s->data);
    s->data = NULL;
    s->len = 0;
    s->cap = 0;
}

static void s_clear(SString *s) {
    s->len = 0;
}

static void s_ensure_cap(SString *s, unsigned int need) {
    if (need <= s->cap) return;

    unsigned int newcap = s->cap;
    while (newcap < need) {
        newcap *= 2;
    }

    char *p = (char *)realloc(s->data, newcap);
    if (p == NULL) {
        exit(1);
    }
    s->data = p;
    s->cap = newcap;
}

static void s_append_char(SString *s, char ch) {
    s_ensure_cap(s, s->len + 1);
    s->data[s->len] = ch;
    s->len++;
}

static void s_set_from_reader(SString *s, int (*nextch)(void), int (*done)(int)) {
    s_clear(s);
    for (;;) {
        int c = nextch();
        if (c == EOF || done(c)) break;
        s_append_char(s, (char)c);
    }
}

static void s_append_from_reader(SString *s, int (*nextch)(void), int (*done)(int)) {
    for (;;) {
        int c = nextch();
        if (c == EOF || done(c)) break;
        s_append_char(s, (char)c);
    }
}

static int is_ws(int c) {
    return c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\v' || c == '\f';
}

static void skip_ws(void) {
    int c;
    while ((c = getchar()) != EOF) {
        if (!is_ws(c)) {
            ungetc(c, stdin);
            return;
        }
    }
}

static int done_on_ws(int c) {
    if (is_ws(c)) {
        ungetc(c, stdin); /* leave delimiter for outer parser */
        return 1;
    }
    return 0;
}

static int done_on_quote(int c) {
    return c == '"';
}

static SString *pick(SString *a, SString *b, SString *c, SString *d, int name) {
    if (name == 'a') return a;
    if (name == 'b') return b;
    if (name == 'c') return c;
    if (name == 'd') return d;
    return NULL;
}

static void s_print(const SString *s) {
    for (unsigned int i = 0; i < s->len; i++) {
        putchar(s->data[i]);
    }
    putchar('\n');
}

static void s_detail(const SString *s) {
    /* Line 1: String: "<contents>" */
    printf("String: \"");
    for (unsigned int i = 0; i < s->len; i++) {
        putchar(s->data[i]);
    }
    printf("\"\n");

    /* Line 2: Length: <len> */
    printf("Length: %u\n", s->len);

    /* Line 3: Capacity: <cap> */
    printf("Capacity: %u\n", s->cap);
}

static void s_assign_concat(SString *dest, const SString *x, const SString *y) {
    unsigned int need = x->len + y->len;
    s_clear(dest);
    s_ensure_cap(dest, need);

    for (unsigned int i = 0; i < x->len; i++) {
        dest->data[i] = x->data[i];
    }
    for (unsigned int j = 0; j < y->len; j++) {
        dest->data[x->len + j] = y->data[j];
    }
    dest->len = need;
}

int main(void) {
    SString a, b, c, d;
    s_init(&a);
    s_init(&b);
    s_init(&c);
    s_init(&d);

    for (;;) {
        skip_ws();
        int cmd = getchar();
        if (cmd == EOF) break;

        if (cmd == 'q') {
            break;
        } else if (cmd == 'p' || cmd == 'd') {
            skip_ws();
            int t = getchar();
            SString *s = pick(&a, &b, &c, &d, t);
            if (s == NULL) continue;

            if (cmd == 'p') s_print(s);
            else s_detail(s);

        } else if (cmd == 'r' || cmd == 'a') {
            skip_ws();
            int t = getchar();
            SString *s = pick(&a, &b, &c, &d, t);
            if (s == NULL) continue;

            skip_ws();
            int first = getchar();
            if (first == '"') {
                /* read until closing quote (quote not included) */
                if (cmd == 'r') s_set_from_reader(s, getchar, done_on_quote);
                else s_append_from_reader(s, getchar, done_on_quote);
            } else {
                /* unquoted token: read until whitespace */
                if (first != EOF) ungetc(first, stdin);
                if (cmd == 'r') s_set_from_reader(s, getchar, done_on_ws);
                else s_append_from_reader(s, getchar, done_on_ws);
            }

        } else if (cmd == 'c') {
            skip_ws();
            int t1 = getchar();
            skip_ws();
            int t2 = getchar();
            skip_ws();
            int t3 = getchar();

            SString *dest = pick(&a, &b, &c, &d, t1);
            SString *s2 = pick(&a, &b, &c, &d, t2);
            SString *s3 = pick(&a, &b, &c, &d, t3);
            if (dest == NULL || s2 == NULL || s3 == NULL) continue;

            s_assign_concat(dest, s2, s3);
        } else {
            /* unknown command: ignore and continue */
        }
    }

    s_free(&a);
    s_free(&b);
    s_free(&c);
    s_free(&d);
    return 0;
}