// write to a block of allocated heap and check the value
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "heapAlloc.h"

int main() {
   assert(initHeap(4096) == 0);
   int* ptr = (int*) allocHeap(sizeof(int));
   assert(ptr != NULL);
   *ptr = 42;   // check pointer is in a writeable page
   assert(*ptr == 42);
   DumpMem();
   exit(0);


}
