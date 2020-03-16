#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <limits.h>
////////////////////////////////////////////////////////////////////////////////
//
// Copyright 2019 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        division.c
// This File:        division.c
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

#define BUFFERSIZE 100

/* Declare global variables*/
int counter = 0;

/* Signal handler method that is called when main detects:
 *	Case 1: a divide by zero operation attempt. Method handles error,
 *  		reports number of successfully completed operations, and
 *  		terminates the program smoothly as opposed to crashing.
 *	Case 2: a termination of ^C from the user keyboard, in which
 *		the program will display number of successfully completed
 *		operations before terminating.
 * Parameters:
 * signum - holds the signal type value
 * s - pointer to the first sigaction struct
 * d - pointer to the second sigaction struct
 */
static void signal_handler(int signum, siginfo_t *s, void *d) {

	if(signum == SIGFPE){
		printf("Error: a division by 0 operation was attempted.\n");
		printf("Total number of operations completed successfully: %d\n", counter);
		printf("The program will be terminated.\n");
		exit(0);
	}else if(signum ==  SIGINT){		
		printf("\n");
		exit(0);

	}
}

/*
 *This method divide num1 by num2. if user input 0 into num2,
 *then program is terminated. Also, if user press control + c,
 *then, program is terminated.
 */
int main (int argc, const char *argv[]) {

	// Declare local variables
	struct sigaction act, oact;
	char buff[BUFFERSIZE];
	int num1, num2;
	int quot;
	int remainder;
	
	// Handle when a signal is thrown
	act.sa_flags = SA_ONSTACK | SA_RESTART | SA_SIGINFO;
	act.sa_sigaction = signal_handler;
	//initialize sigaction SIGINT and SIGFPE to the structure
	 sigaction(SIGFPE, &act, &oact); 
	sigaction(SIGINT, &act, &oact); 
	
	
	while (1) { // infinity loop until control+C or divide by zero
	
		// Get denominator from keyboard
		printf("Enter first integer: ");
	
		if (fgets(buff, BUFFERSIZE, stdin) != NULL) {
		num1 = atoi(buff);	
		    // Get numerator from keyboard
		printf("Enter second integer: ");
	
			if (fgets(buff, BUFFERSIZE, stdin) != NULL) {
			num2 = atoi(buff);
			}
		}
		quot = num1 / num2;
		
		remainder = num1 % num2;
		
		// Display the result
		printf("%d / %d is %d with a remainder of %d\n", num1, num2, quot, remainder);
		
		// increments counter
		counter++;
	}
	
	return 0;
}
