#include <stdio.h>

int main(void) {
    int c;
    int n = 0;              // number of digits read
    int sum_even = 0;       // Luhn sum if total length is even
    int sum_odd = 0;        // Luhn sum if total length is odd

    while ((c = getchar()) != EOF) {
        if (c < '0' || c > '9') break;

        int d = c - '0';

        /* If total length is even:
           positions 1,3,5,... (from left, 1-based) are doubled (because the check digit is last).
           If total length is odd:
           positions 2,4,6,... are doubled.
        */
        int pos = n + 1; // 1-based position from the left

        // update sum_even
        if (pos % 2 == 1) {
            int x = d * 2;
            if (x >= 10) x -= 9;
            sum_even += x;
        } else {
            sum_even += d;
        }

        // update sum_odd
        if (pos % 2 == 0) {
            int x = d * 2;
            if (x >= 10) x -= 9;
            sum_odd += x;
        } else {
            sum_odd += d;
        }

        n++;
    }

    if (n == 0) {
        puts("Invalid");
        return 0;
    }

    int sum = (n % 2 == 0) ? sum_even : sum_odd;

    if (sum % 10 == 0) {
        puts("Valid");
    } else {
        puts("Invalid");
    }

    return 0;
}