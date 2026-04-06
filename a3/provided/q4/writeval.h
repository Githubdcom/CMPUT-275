

/*
* writeValue writes the given data into the given memory location 
* (while also writing neceessary "breadcrumb" information into that memory area)
* and returns a pointer to the free space immediately after writeLoc.
*
* writeLoc    - A pointer to free memory where this function should write its
*               breadcrumb data as well as the requested payload.
* type        - A c-string which tells us what type of data payload points
*               at. May be oen of "int", "char", "ptr", or "str".
* payload     - A pointer to some data we want to write to the free memory given.
*               Since this data may actually be an int, a char, a pointer, or a c-string
*               we receive a void * which we must treat as a pointer to whatever data appropriate
*               based on the string given to us in type.
*
* returns      - A pointer to the free memory after writeLoc. That is, the address that comes
*                after we have used space for both our breadcrumb data as well as our payload data.
* side effects - Mutates the memory at writeLoc to contain first our breadcrumb data as well as our
                 payload data subsequent to that.
*/
void *writeValue(void *writeLoc, const char *type, void *payload);


/*
* printValues takes a pointer to some memory that has been written to with our writeValue function
* and prints out all values that were written to memory in order.
* 
* dataStart    - the start of memory that has been written to using zero or more calls to writeValue.
*                guaranteed the memory as been written to with writeValue or it is 1-initialized 
*                (meaning all bits will be 1).
*
* returns      - Nothing
*
* side effects - prints to the screen all values that were written to memory starting at dataStart.
*/
void printValues(void *dataStart);

