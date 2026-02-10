#include <stdio.h>

unsigned int str_replace(char arr[], char tar, char repl) {
  // replaces each occurrence of tar in arr with repl
  // and returns the number of items replaced
  unsigned int cnt = 0;
  for (; *arr; ++arr) {
    if (*arr == tar) {
      *arr = repl;
      ++cnt;
    }
  }
  return cnt;
}
int main() {
  char s[] = "test one";
  printf("'%s' before replacing\n", s);
  str_replace(s, 'e', 'x');
  printf("'%s' after replacing e with x\n", s);
}
