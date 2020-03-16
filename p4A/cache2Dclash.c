int arr2D[128][8];


///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2019 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
//
///////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Main File:        cache2Dclash.c
// This File:        cache2Dclash.c
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
//////////////////////////// 80 columns wide /////////////////////////////////

/**
 *cache2Dclash.c has a 2-dimensional global array of integers having 
 dimensions 128 rows x 8 columns. In the main() function,
 *
**/

int main(){

for(int i = 0 ; i <100  ; i++ ){
//The outermost loop repeats this 100 times.	
	for(int row =0 ;row < 128 ;row += 64){
//middle loop iterates over the rows, incrementing by 64 instead of 1
		for(int col =0 ; col < 8 ; col++ ){
// The innermost loop iterates over the columns of the array
			arr2D[row][col] = i + row + col;
	
		
		}
	}
}



}
