// allocation is too big to fit
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "heapAlloc.h"

int main() {
	printf("init heap!");
    assert(initHeap(4096)  == 0);
    printf("no space test stats");
    assert(allocHeap(1)    != NULL);
    printf("allocate 1 properly");
    assert(allocHeap(4095) == NULL);
        printf("requested size Too big ");
       DumpMem();
    exit(0);
}
