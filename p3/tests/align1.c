// first pointer returned is 8-byte aligned
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include "heapAlloc.h"

int main() {
   assert(initHeap(4096) == 0);
   printf("passed initHeap");
   int* ptr = (int*) allocHeap(sizeof(int));
   assert(ptr != NULL);
   printf("ptr is not null");
   assert(((int)ptr) % 8 == 0);
   printf("pointer's address is multiple of 8");
   printf("done");
   DumpMem();
   exit(0);
}
