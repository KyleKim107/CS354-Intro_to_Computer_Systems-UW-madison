///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2019 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
//
///////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Main File:        heapAlloc.c
// This File:        heapAlloc.c
// Other Files:      N/A
// Semester:         CS 354 Fall 2019
//
// Author:           Deho Kim
// Email:            dkm577@wisc.edu
// CS Login:         deho
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of
//                   of any information you find.
//////////////////////////// 80 columns wide ///////////////////////////////////


#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include "heapAlloc.h"

/*
 * This structure serves as the header for each allocated and free block.
 * It also serves as the footer for each free block but only containing size.
 */
typedef struct blockHeader {
        int size_status;
    /*
    * Size of the block is always a multiple of 8.
    * Size is stored in all block headers and free block footers.
    *
    * Status is stored only in headers using the two least significant bits.
    *   Bit0 => least significant bit, last bit
    *   Bit0 == 0 => free block
    *   Bit0 == 1 => allocated block
    *
    *   Bit1 => second last bit
    *   Bit1 == 0 => previous block is free
    *   Bit1 == 1 => previous block is allocated
    *
    * End Mark:
    *  The end of the available memory is indicated using a size_status of 1.
    *
    * Examples:
    *
    * 1. Allocated block of size 24 bytes:
    *    Header:
    *      If the previous block is allocated, size_status should be 27
    *      If the previous block is free, size_status should be 25
    *
    * 2. Free block of size 24 bytes:
    *    Header:
    *      If the previous block is allocated, size_status should be 26
    *      If the previous block is free, size_status should be 24
    *    Footer:
    *      size_status should be 24
    */


} blockHeader;

/* Global variable - DO NOT CHANGE. It should always point to the first block,
 * i.e., the block at the lowest address.
 */

blockHeader *heapStart = NULL; // global variables for the allocHeap() and freeHeap method
blockHeader *current = NULL;
blockHeader *heapEnd= NULL;
int heapsize = 0;
int freeSize = 0;
 blockHeader *curr = NULL;

 /*
 * Function for allocating 'size' bytes of heap memory.
 * Argument size: requested size for the payload
 * Returns address of allocated block on success.
 * Returns NULL on failure.
 * This function should:
 * - Check size - Return NULL if not positive or if larger than heap space.
 * - Determine block size rounding up to a multiple of 8 and possibly adding padding as a result.
 * - Use NEXT-FIT PLACEMENT POLICY to chose a free block
 * - Use SPLITTING to divide the chosen free block into two if it is too large.
 * - Update header(s) and footer as needed.
 * Tips: Be careful with pointer arithmetic and scale factors.
 */
void* allocHeap(int size) { // The size mean what the user want to allocate

printf("\nallcHeap srats!\n");

if (curr == NULL){
       	curr = heapStart;
int Totalheap = heapStart->size_status >> 2 << 2;
heapEnd = (blockHeader*)((void*)heapStart + Totalheap); // calculate address of end mark once
}
int currentSize = 0;  //initiallizing variables
int nextBlockSize = 0;

/**
  *  If the size is less than 0 then return NULL
  */
 if(size <= 0 || size > heapsize - 8){
      return NULL;
    }

    size = size + 4; // adding header.

 if(size % 8 !=0){

     size = (( size / 8)+1) *8; // making multiple of 8 to header.

    }

 if(current == NULL){
     current =curr;

  }

blockHeader *prev = current;

int valid = 0;

while(valid == 0){

	currentSize = current -> size_status >> 2 << 2;

	if((current -> size_status &1)==1){ // check it is alloccated.
		    if( (current -> size_status & 1) == 1){ // dummy if-statement to maintain this structure
			    // Using next fit. go to the next block.

			current = (blockHeader*)((char*)(current)+currentSize);

   		       }


   	 }else{ // when the block is free

   	 freeSize = current -> size_status >> 2 << 2; // get the size of the free block
   	 // 10100110 >>2 = 101001
   	 // 101001 << 2 = 10100100 we want to get first five number, which is size.

 	 blockHeader* nextBlock = current;

                if(freeSize < size ){ // if the requested size is bigger than free block, move for the next block.
    	        current = (blockHeader*) ((char*)current + freeSize ); // +4 or not.

	        }else{// check if we can split

			int LeftOver =freeSize - size;
			if(LeftOver >= 8){
			//	nextBlock = (blockHeader*)( (void*) current + size); //moves the NextBlock Ptr as much as the size.
				// split
				int p = current ->size_status & 2; // keep the p-bit of current
				current -> size_status = size; // update size
				current ->size_status += p; // update p-bit
				current ->size_status += 1; // update a-bit.

				nextBlock = (blockHeader*)((void*)current + size);
				nextBlock -> size_status = LeftOver; //update size
				nextBlock -> size_status += 2; // updatig p bit
				blockHeader* footer = (blockHeader*) ((char*)nextBlock +(LeftOver) - 4);
				// go as much as size and subtract// 4 to go back to the footer.

				footer -> size_status = LeftOver;
				return (void*)current +4;

			}else{ // not split case

				current -> size_status += 1;   // change allocation sign into the header ( size /1 ).

				nextBlock = (blockHeader*)((void*) current + freeSize);
				nextBlock  -> size_status += 2;
				return (void*) current +4;

             		}
		}

	 }

	if(current->size_status == 1){// reaches end of heap
	current = heapStart;

	}

	if(current ==prev){ // we go back to where we start havingdone searchig for one round failing
	return NULL;

	}

    }
         return NULL;


  }


//blockHeader *freePtr = NULL;
/*
 * Function for freeing up a previously allocated block.
 * Argument ptr: address of the block to be freed up.
 * Returns 0 on success.
 * Returns -1 on failure.
 * This function should:
 * - Return -1 if ptr is NULL. -o
 * - Return -1 if ptr is not a multiple of 8. -o
 * - Return -1 if ptr is outside of the heap space.
 * - Return -1 if ptr block is already freed.
 * - USE IMMEDIATE COALESCING if one or both of the adjacent neighbors are free.
 * - Update header(s) and footer as needed.
 */
int freeHeap(void *ptr) {
  if(ptr == NULL ){  //return -1 if ptr is null
	return -1;
  }
  printf("ptr is not NULL\n");

  if((int)ptr % 8 != 0  ){// not multiple of 8.
  return -1;
  }
  printf("ptr is multiple of 8.\n");

  if(ptr  >= (void*)heapEnd ){ //return -1 if ptr is outside of the heap space.
  return -1;
  }
  printf("ptr isn't out of heap space\n");

  blockHeader *freePtr = (void*)ptr -4; // get current header
  if((((blockHeader*)freePtr)-> size_status & 1) != 1) {//checks a - bit return -1 if ptr block is already freed.
  return -1;
 }
 printf("ptr is free\n");





  int currentSize = 0;

//blockHeader *freePtr = (blockHeader*)((void*)ptr - 4); // -4 to get the current header.

  freePtr -> size_status -= 1; // change the size_status as size/0.
  currentSize = (freePtr -> size_status  >> 2 << 2); // get the current size.

//check next bloock for coalescing
  blockHeader *nextBlock = ((void*)freePtr + currentSize); // sets the nextPtr to the next blockheader.
  nextBlock -> size_status -= 2;// subtract the next block's p bit.!!!!!
  int nextBsize = 0;
  int newSize = currentSize; // add the size of the current block


if((nextBlock -> size_status & 1)  == 0 ){  // case the next block is free, otherwise check previous block.
    nextBsize = nextBlock -> size_status >> 2 << 2; // get the size of the next block
    newSize += nextBsize;// add size of current and nextBlock each other.
    freePtr->size_status += nextBsize; // in case the current block has the header.

     blockHeader *oneMoreNext = (blockHeader*)((void*)nextBlock + nextBsize);

}

int ptr_p_bit = ((blockHeader*)freePtr)->size_status & 2; // get the p - bit of current block


if(ptr_p_bit != 2) {// when the previous block is free
    blockHeader *prev_footer =(blockHeader*)((char*) freePtr - 4); // - 4 to get the prev-Footer
    int sizeOfpreB = prev_footer -> size_status;// get the previous block's size.

    freePtr = (blockHeader*)((void*) freePtr - sizeOfpreB); // subtract as much as size of previous block

    freePtr -> size_status += newSize; // add size of the front of two blocks.
    newSize = freePtr ->size_status >> 2 << 2; // assign the total size to the newSize variable to
    printf("prevBlock coalesced size=%d\n", newSize);
    curr = freePtr;
}
	printf("newSize %d\n",newSize);
	// CREAT FOOTER

	blockHeader *Footer =(blockHeader*)( (void*)freePtr + newSize - 4);
	Footer->size_status = newSize;

   	 return 0; // if the free is successful
}










/*
 * Function used to initialize the memory allocator.
 * Intended to be called ONLY once by a program.
 * Argument sizeOfRegion: the size of the heap space to be allocated.
 * Returns 0 on success.
 * Returns -1 on failure.
 */
int initHeap(int sizeOfRegion) {
    heapsize = sizeOfRegion;
    static int allocated_once = 0; //prevent multiple initHeap calls

    int pagesize;  // page size
    int padsize;   // size of padding when heap size not a multiple of page size
    int allocsize; // size of requested allocation including padding
    void* mmap_ptr; // pointer to memory mapped area
    int fd;

    blockHeader* endMark;

    if (0 != allocated_once) {
        fprintf(stderr,
        "Error:mem.c: InitHeap has allocated space during a previous call\n");
        return -1;
    }
    if (sizeOfRegion <= 0) {
        fprintf(stderr, "Error:mem.c: Requested block size is not positive\n");
        return -1;
    }

    // Get the pagesize
    pagesize = getpagesize();

    // Calculate padsize as the padding required to round up sizeOfRegion
    // to a multiple of pagesize
    padsize = sizeOfRegion % pagesize;
    padsize = (pagesize - padsize) % pagesize;

    allocsize = sizeOfRegion + padsize;

    // Using mmap to allocate memory
    fd = open("/dev/zero", O_RDWR);
    if (-1 == fd) {
        fprintf(stderr, "Error:mem.c: Cannot open /dev/zero\n");
        return -1;
    }
    mmap_ptr = mmap(NULL, allocsize, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (MAP_FAILED == mmap_ptr) {
        fprintf(stderr, "Error:mem.c: mmap cannot allocate space\n");
        allocated_once = 0;
        return -1;
    }

    allocated_once = 1;

    // for double word alignment and end mark
    allocsize -= 8;

    // Initially there is only one big free block in the heap.
    // Skip first 4 bytes for double word alignment requirement.
    heapStart = (blockHeader*) mmap_ptr + 1; // adding 4 byte of header

    // Set the end mark
    endMark = (blockHeader*)((void*)heapStart + allocsize);
    endMark->size_status = 1;

    // Set size in header
    heapStart->size_status = allocsize;

    // Set p-bit as allocated in header
    // note a-bit left at 0 for free
    heapStart->size_status += 2;

    // Set the footer
    blockHeader *footer = (blockHeader*) ((char*)heapStart + allocsize - 4); //move n byte and subtrac 4 to get footer
    footer->size_status = allocsize; // Only free block has the footer
    DumpMem();
    return 0;
}

/*
 * Function to be used for DEBUGGING to help you visualize your heap structure.
 * Prints out a list of all the blocks including this information:
 * No.      : serial number of the block
 * Status   : free/used (allocated)
 * Prev     : status of previous block free/used (allocated)
 * t_Begin  : address of the first byte in the block (where the header starts)
 * t_End    : address of the last byte in the block
 * t_Size   : size of the block as stored in the block header
 */
void DumpMem() {

    int counter;
    char status[5];
    char p_status[5];
    char *t_begin = NULL;
    char *t_end   = NULL;
    int t_size;

    blockHeader *current = heapStart;
    counter = 1;

    int used_size = 0;
    int free_size = 0;
    int is_used   = -1;

    fprintf(stdout, "************************************Block list***\
                    ********************************\n");
    fprintf(stdout, "No.\tStatus\tPrev\tt_Begin\t\tt_End\t\tt_Size\n");
    fprintf(stdout, "-------------------------------------------------\
                    --------------------------------\n");

    while (current->size_status != 1) {
        t_begin = (char*)current;
        t_size = current->size_status;

        if (t_size & 1) {
            // LSB = 1 => used block
            strcpy(status, "used");
            is_used = 1;
            t_size = t_size - 1;
        } else {
            strcpy(status, "Free");
            is_used = 0;
        }

        if (t_size & 2) {
            strcpy(p_status, "used");
            t_size = t_size - 2;
        } else {
            strcpy(p_status, "Free");
        }

        if (is_used)
            used_size += t_size;
        else
            free_size += t_size;

        t_end = t_begin + t_size - 1;

        fprintf(stdout, "%d\t%s\t%s\t0x%08lx\t0x%08lx\t%d\n", counter, status,
        p_status, (unsigned long int)t_begin, (unsigned long int)t_end, t_size);

        current = (blockHeader*)((char*)current + t_size);
        counter = counter + 1;
    }

    fprintf(stdout, "---------------------------------------------------\
                    ------------------------------\n");
    fprintf(stdout, "***************************************************\
                    ******************************\n");
    fprintf(stdout, "Total used size = %d\n", used_size);
    fprintf(stdout, "Total free size = %d\n", free_size);
    fprintf(stdout, "Total size = %d\n", used_size + free_size);
    fprintf(stdout, "***************************************************\
                    ******************************\n");
    fflush(stdout);

    return;
}
