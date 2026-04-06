// In reality we would grab the page size from the OS with getpagesize()
// However, since this getPage must return back to students a pointer to
// a block of known number of bytes we have hardcoded the page size of 4096
// (which just happens to be a very common page size as well as Ohaton's)
#define PAGESIZE 4096

// Returns a pointer to an allocated block of size PAGESIZE.
// Subsequent allocations are always contiguous. Meaning if the
// client asks for an allocation larger than PAGESIZE you can allocate
// multiple contiguous pages to satisfy their request.
void *getUserPage();

// Returns a pointer to an allocated block of size PAGESIZE.
// Subsequent allocations are always contiguous. Meaning if your
// allocator requires a single allocation larger than PAGESIZE (should be unnecessary)
// then subsequently allocated pages can be used to satisfy that requirement.
void *getSysPage();

// Returns a page allocated with getPage back to the OS.
// The provided argument /must/ be a pointer that was returned
// by the function getUserPage() or getSysPage.
void releasePage(void *);