#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////
//
// Copyright 2019 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        intdate.c
// This File:        sendsig.c
// Other Files:       division.c, sendsig.c, intdate.c
// Semester:         CS 354 Fall 2019
//
// Author:           DEHO KIM
// Email:            dkim577@wisc.edu
// CS Login:         deho
//////////////////////////// OTHER SOURCES OF HELP /////////////////////////////
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

/**
 *this method send a signal to the intdate 
 *
 */
int main(int argc, char *argv[]){

 int pid = atoi(argv[2]);

 //printing out sample formats.
       	 if (argc != 3) {
                printf("Usage: <signal type> <pid>\n");
       		
	 }else if(strcmp(argv[1],"-i") == 0) {   //grabs the command line inputs and compares them             
                
                        //kill(pid , sig ) send a signal with the sig behavior.
                        kill(pid, SIGINT);
	
	  }else if (strcmp(argv[1],"-u") == 0){
                        //kill(pid , sig ) send a signal with the sig behavior.
                        kill(pid, SIGUSR1);
                }
       
        return 0;

}
