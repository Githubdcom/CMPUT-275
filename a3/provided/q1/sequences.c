#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Operation {
    char op[4];
    int val;
    struct Operation *next;
};

int apply_op(int current, char *op, int val) {
    if (strcmp(op, "add") == 0) return current + val;
    if (strcmp(op, "sub") == 0) return current - val;
    if (strcmp(op, "mul") == 0) return current * val;
    if (strcmp(op, "div") == 0) return current / val;
    return current; // Should not reach here with valid input
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <initial_value>\n", argv[0]);
        return 1;
    }
    int initial = atoi(argv[1]);
    int current = initial;
    struct Operation *head = NULL;
    struct Operation *tail = NULL;
    char op_str[10];
    int val;
    while (scanf("%s", op_str) != EOF) {
        if (strcmp(op_str, "n") == 0) {
            int temp = current;
            struct Operation *ptr = head;
            while (ptr != NULL) {
                temp = apply_op(temp, ptr->op, ptr->val);
                ptr = ptr->next;
            }
            printf("%d\n", temp);
            current = temp;
        } else {
            if (scanf("%d", &val) != 1) {
                // Handle invalid input (non-integer after operator)
                fprintf(stderr, "Invalid input: expected integer after operator\n");
                // Free memory and exit
                struct Operation *ptr = head;
                while (ptr != NULL) {
                    struct Operation *next = ptr->next;
                    free(ptr);
                    ptr = next;
                }
                return 1;
            }
            struct Operation *new_op = malloc(sizeof(struct Operation));
            if (new_op == NULL) {
                // Handle malloc failure
                fprintf(stderr, "Memory allocation failed\n");
                // Free existing and exit
                struct Operation *ptr = head;
                while (ptr != NULL) {
                    struct Operation *next = ptr->next;
                    free(ptr);
                    ptr = next;
                }
                return 1;
            }
            // Ensure op_str fits (max 3 chars + null)
            strncpy(new_op->op, op_str, sizeof(new_op->op) - 1);
            new_op->op[sizeof(new_op->op) - 1] = '\0';
            new_op->val = val;
            new_op->next = NULL;
            if (tail == NULL) {
                head = tail = new_op;
            } else {
                tail->next = new_op;
                tail = new_op;
            }
        }
    }
    // Free the linked list
    struct Operation *ptr = head;
    while (ptr != NULL) {
        struct Operation *next = ptr->next;
        free(ptr);
        ptr = next;
    }
    return 0;
}