///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2019 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        n_in_a_row
// This File:        n_in_a_row.c
// Other Files:      (name of all other files if any)
// Semester:         CS 354 Fall 2019
//
// Author:           Deho Kim
// Email:            dkim577@wisc.edu
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
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>  
#include <stdlib.h>
#include <string.h>     

char *COMMA = ",";  

/* COMPLETED:       
 * Retrieves from the first line of the input file,
 * the size of the board (number of rows and columns).
 * 
 * fp: file pointer for input file
 * size: pointer to size
 */
void get_dimensions(FILE *fp, int *size) {      
    char *line = NULL;
    size_t len = 0;
    if (getline(&line, &len, fp) == -1) {
        exit(1);
    }

    char *token = NULL; // Declaring pointer.
    token = strtok(line, COMMA); // Assinging input into the token.
    *size = atoi(token); // Converting from String to int.
}   


/* TODO:
 * Returns 1 if and only if the board is in a valid state.
 * Otherwise returns 0.
 * 
 * board: heap allocated 2D board
 * size: number of rows and columns
 */
int n_in_a_row(int **board, int size) {

int numX=0; // Declaring the local variables.
int numO=0;
int value=0;
int coincident=0;
int winner=0 ;

for(int i =0; i<size ; ++i){ //  figure out whether this board is valid or not
   for(int k =0; k< size ; ++k){
	   value = *(*(board+i)+k);// value of each array.

if(value==1){ //counting number of X
++numX;
}
if(value ==2){ // counting number of O
++numO;
      }	 
    }
  }
// if the number of X is lower than O, fail
if( numX >( 1+ numO) || (numX < numO)) { 
return 0;
}


for(int i =0 ; i < size ; ++i){ 
	// Checking eveyrow whether there is same marks as much as the size.
	value = **(board+i); // pointing first array in first column.
	for(int k = 0 ; k < size ; ++k){ 
		if(value == 0){
		break;
		}
		if(*(*(board+i)+k) ==  value){//comparing the of value with others. 
			++coincident; //Increment		
		}
	
	}	
	}	
if((value == 1) && (coincident == size) ){   	// if there is numbe of coincident as much as size.
		++winner;
	}
if((value == 2)&&(numX == numO) && (coincident == size)){
++winner;
}

coincident = 0; 



for(int i =0 ; i < size ; ++i){ //Vertical Check
       	// Setting a value of every array of the first array.
        value = *(*(board)+i); 

	for(int k = 0 ; k < size ; ++k){ //looping the 2d array
		if(value == 0){
                break;
                }
		if(*(*(board +i)+k) == value){
					
			++coincident;
			}	
		}
	if((value == 1) && (coincident == size) ){
 //Horizontal Check.            // if there is numbe of coincident as much as size.
                ++winner;
        }
	if((value == 2)&&(numX == numO) && (coincident == size)){
		++winner;
	}


	coincident = 0;
	}

value = **board; // Diagonal test
for(int i=0 ; i < size ; ++i){
	for(int k=0; k<size ;++k){
		if(value == 0){
                break;
                }
		if(i==k){ // the precondition of the diagonal arrays.
			if(*(*(board + i ) + k) == value){++coincident;	}
		
			}	 
		}
		if((value == 1) && (coincident == size) ){
	 //Horizontal Check.            // if there is numbe of coincident as much as size.
                ++winner;
       			 }
		if((value == 2)&&(numX == numO && coincident == size )){
		++winner;
		}	

		coincident = 0;
}


coincident = 0 ;

value = *(*(board+(size-1))); // Anti- Diagonal test	
for(int i = 0 ; i < size ; i++){
	for(int k =0 ; k < size ; ++k){
		if(value == 0){
                break;
                }
		if((i+k) == (size - 1)){ // precondition of anti-diagonal.
			if(*(*(board +i)) == value){
				++coincident;
			}
		}		
	}
		if((value == 1) && (coincident == size) ){
 //Horizontal Check.            // if there is numbe of coincident as much as size.
                ++winner;
        }
if((value == 2)&&(numX == numO) && (coincident == size)){
++winner;
}					
}

if(winner ==1 || winner ==0){ //There should be either one winner or nobody.
	return 1;
}

      return 0;
}     


/* PARTIALLY COMPLETED:
 * This program prints Valid if the input file contains
 * a game board with either 1 or no winners; and where
 * there is at most 1 more X than O.
 * 
 * argc: CLA count
 * argv: CLA value
 */
int main(int argc, char *argv[]) {              
    
    //TODO: Check if number of command-line arguments is correct.
    if(argc != 2){
 printf("The number of command line isn't correct."); 
	    exit(1);
    }
   
    //Open the file and check if it opened successfully.
    FILE *fp = fopen(*(argv + 1), "r");
    if (fp == NULL) {
        exit(1);
   }
    //Declare local variables.
    int size = 0;
    //TODO: Call get_dimensions to retrieve the board size.
       get_dimensions( fp, &size); // getting the size of the array.

     
    //TODO: Dynamically allocate a 2D array of dimensions retrieved above.
	int **x = malloc(sizeof(int*)*size); // creating 2D array
	
	for(int i = 0; i<size ;++i ) {
       	 *(x+i) = malloc(sizeof(int)*size);

       }
 
    //Read the file line by line.
    //Tokenize each line wrt comma to store the values in your 2D array.
    char *line = NULL;
    size_t len = 0;
    char *token = NULL;
    
    for (int i = 0; i < size; i++) {
        if (getline(&line, &len, fp) == -1) {
           
            exit(1);
        }
        token = strtok(line, COMMA);
        for (int j = 0; j < size; j++){
	    	
            //TODO: Complete the line of code below
            //to initialize your 2D array.
            *(*(x+i)+j) = atoi(token);// Initialize
            token = strtok(NULL, COMMA);
	}
    } 
   
    //TODO: Call the function n_in_a_row and print the appropriate
    //output depending on the function's return value.
int valid = n_in_a_row(x, size);// get the validity of game.
if(valid == 1){
printf("\nthis game is valid!\n");
}else{
printf("\nThis game is invalid!\n");
}
    //TODO: Free all dynamically allocated memory.
    //
for(int i = 0 ; i < size ; ++i){//freed the all the allocations.
free(*(x+i));
}
free(x);
x = NULL;
	
    //Close the file.
    if (fclose(fp) != 0) {
        exit(1);
    } 
    
    return 0;       
}       

