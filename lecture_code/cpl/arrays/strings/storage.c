#include <stdio.h>

int main() {
  char myS[] = "This is stored on the stack";
  // Because I explicitly declared myS as an array of characters
  // the same thing that happens when I say int arr[] = {1, 2, 3} is
  // happening here. Which is to say, that enough space is allocated
  // on the stack to store collection on the right hand side of the assignment
  // So in this case I literally have an array of characters on my stack
  printf("%s\n", myS);
  myS[0] = 'X'; // Set the first character in that array to 'X'
  printf("%s\n", myS);
  char *p = "This is stored in the text or data segment";
  printf("%s\n", p);
    // Trying to write to the memory p points at crashes my program...
    /// uncomment the lines below and see
//  p[0] = 'X'; // Set the first character in the array p points at to 'X'
//  printf("%s\n", p);
  printf("address of myS: %p\n", myS);
  printf("address that p points at: %p\n", p);
}
