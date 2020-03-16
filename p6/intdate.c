#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <limits.h>
#include <string.h>
////////////////////////////////////////////////////////////////////////////////
//
// Copyright 2019 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        intdate.c
// This File:        intdate.c
// Other Files:	      division.c, sendsig.c, intdate.c
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

//global variable for counter and alarm setting.
int counter = 0;
int alarmSec = 3;



static void signal_handler(int sigNum, siginfo_t *si , void *d) {

        time_t currtime;

        if(sigNum == SIGALRM){ // print out current time after 3 sec of signal call 

                time(&currtime);
                printf("PID: %d | Current Time: %s", getpid(), ctime(&currtime));
                alarm(alarmSec);

          return;
        }else if(sigNum == SIGUSR1){ //received siguser1

                counter++;
                printf("SIGUSR1 caught!\n");

          return;
        }else if(sigNum == SIGINT){ // program terminated 

                printf("\nSIGINT received.\n");
                 printf("SUGUSR1 was received %d times. Exiting now.\n", counter);

        exit(0);
        return;
        }

}


/**
 * main method initialize signal action. Also main receives singnal call
 *  to trigger the signal's action. 
 *
 *
 */
int main(int argc, const char *argv[]) {
	
	// Create sigaciton structure 
	struct sigaction act, osa;
	memset(&act, 0, sizeof(act));
	act.sa_flags = 0;
	// assign handler to the act
	act.sa_sigaction = signal_handler;

	// Setting signal when SIGALRM is called
	sigaction(SIGALRM, &act, &osa);

	//Setting signal when SIGSR1 is called
	sigaction(SIGUSR1, &act, &osa);

	//Setting signal when SIGINT is called
	sigaction(SIGINT, &act, &osa);

	// Set the initial alarm, which will then send the signal
	// every 3 seconds.
	alarm(alarmSec);
	
	printf("Pid and time will be printed every 3 seconds.\n");
	printf("Enter ^C to end the program.\n");
	
	// Infinite loop to have the program run until ^C is signalled
	while(1);

	return 0;

}



