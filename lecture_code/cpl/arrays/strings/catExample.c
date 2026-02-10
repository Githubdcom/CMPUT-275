#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
  char s2[4] = "abc";
  char s1[16] = "hello";

  strcat(s1, s2); // Okay! enough space in s1!
  // s1 now stores "helloabc" meaning 9 characters
  // of the array are used (note null terminator must be there!)
  printf("%s\n", s1);
  char s3[12] = "this is big";
  strcat(s1, s3); // ERROR! Undefined behaviour! Dest array not large enough!
  char *buff = malloc(256*sizeof(char)); // Don't worry about this yet...
  scanf("%255s", buff);
  strcat(s1, buff);
  printf("s1: %s\n", s1);
  printf("s2: %s\n", s2);
  printf("s3: %s\n", s3);
}
