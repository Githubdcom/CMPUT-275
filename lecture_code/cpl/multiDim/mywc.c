#include <stdio.h>
#include <string.h>
int isws(char c) {
  return (c == '\n' || c == ' ' || c == '\t' || c == '\r');
}

int main(int argc, char **argv) {
  int cc = 0; // char count
  int wc = 0; // word count
  int lc = 0; // line count
  char c = 0;
  char prevChar = ' ';
  while ((c = getchar()) != EOF) {
    // Techically recall that getChar returns an int
    // and I should be checking for failures there...
    ++cc;
    if (c == '\n') ++lc;
    if (isws(prevChar) && !isws(c)) ++wc;
    prevChar = c;
  }
  int pc = argc == 1 ? 1 : 0;
  int pl = argc == 1 ? 1 : 0;
  int pw = argc == 1 ? 1 : 0;
  for (int i = 1; i < argc; ++i) {
    if (strcmp(argv[i], "-l") == 0) pl = 1;
    if (strcmp(argv[i], "-c") == 0) pc = 1;
    if (strcmp(argv[i], "-w") == 0) pw = 1;

  }
  if (pl) printf("\t%d", lc);
  if (pw) printf("\t%d", wc);
  if (pc) printf("\t%d", cc);
  printf("\n");
}
