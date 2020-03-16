






///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2019 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
//
///////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Main File:        cache2Dcols.c
// This File:        cache2Dcols.c
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
 *cache2Dcols.c has the same 2D array as above but now the traverses the array
 *in a column-wise order.
 **/

int arr2DCol [3000][500];


int main(){

for(int col = 0 ; col < 500 ; col++){ // he outer loop iterate through the 
					//columns of the array.
	for(int row = 0 ; row < 3000 ; row++){ // an inner loop iterate
	       //through the elements of a single column of the array,
	
arr2DCol[row][col] = row + col;



	}
}


}
