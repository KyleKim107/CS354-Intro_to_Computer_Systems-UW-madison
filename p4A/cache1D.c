
///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2019 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
//
///////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Main File:        cache1D.c
// This File:        cache1D.c
// Other Files:      cache1D.c cache2Drows.c cache2Dcols.c  cache2Dclash.c
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
//////////////////////////// 80 columns wide //////////////////////////////////

/**
 *Declare a global array of integers of size 100,000 before the main() function, 
 *so that this array will be in the data segment.
 **/
int arr[ 1000000];

int main(){


for(int i = 0 ; i < 1000000 ; i++){// iterate over the entire array and
//set the value of each element in the array to its index.
arr[i] = i;

}

}
