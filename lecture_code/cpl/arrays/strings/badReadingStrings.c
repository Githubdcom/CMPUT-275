#include <stdio.h>

int isws(int c) {
  // returns true if C is ws or EOF
  return c == ' ' || c == '\n' || c == '\t' || c == EOF;
}

// A note on scanf("%s, p), readStr below simulates more or less what
// scanf in the above fn call does
int readStr(char *p) {
  int c = getchar();
  while (isws(c)) {
    if (c == EOF) return 0;
    c = getchar(); // Read until first non-ws char
  }
  while (!isws(c)) {
    // if prefix increment was used here, this loop would be
    // incorrect!
    *p++ = c;
    c = getchar();
  }
  *p = '\0';
  return 1;
}

int fib(int n) {
  if (n == 0 || n == 1) return 1;
  return fib(n-1) + fib(n-2);
}

int main() {
  // strings can be read-in with scanf, but that can be a dangerous game...
  // Our arrays are fixed sizes and a string that scanf reads in is as many
  // characters as it sees until it sees a white space (or end of file).
  char s[16];
  const char myConst[] = "this is a constant string for use later";
  int x = 5;
  char c = 'A';
  // DANGER! DANGER! UNSAFE!
  scanf("%s", s); // asking scanf to read a string into my array s...
  printf("I received: '%s'\n", s);
  printf("%d==5, %c=='A'\n", x, c);
  printf("const str: '%s'\n", myConst);
//  printf("By the way, fib(8) is %d\n", fib(8));
  printf("The read in string is now %s\n", s);
  readStr(s);
  printf("The new string read in: %s\n", s);
  // The above causes issues when the user types a string that is
  // longer than 15 characters because the array s only has space
  // for 16 characters (15 actual characters + 1 null terminator)
  // scanf does not know how large the array is, it simply reads
  // characters until it sees something to end the str (whitespace
  // or EOF) and writes those characters to the contiguous addresses
  // started at the one you gave.
  // That means in this case when the user types a string larger
  // than 15 characters we simply write all the characters past
  // the 15th into our stack after the end of our array... which
  // could be more of our stack variables, could be garbage space,
  // we don't know!
}
