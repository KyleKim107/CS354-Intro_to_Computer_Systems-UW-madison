///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2019 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
//
///////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Main File:        cache2Drows.c
// This File:        cache2Drows.c
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
//////////////////////////// 80 columns wide ///////////////////////////////////

/**
 * cache2Drows.c has a 2-dimensional global array of integers having dimensions
 * 3000 rows x 500 columns. In the main() function
 *
 **/


int arr2D[3000][500];

int main(){

for(int row = 0 ; row < 3000; row++){
// an outer loop iterate through the rows of the array.	
	for(int col = 0 ; col <500 ; col++){
//an inner loop iterate through the elements of a single row of the array
		arr2D[row][col] = row + col;

	}
}

}
