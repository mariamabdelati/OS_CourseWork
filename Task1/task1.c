/*
KH5004CEM Operating Systems and Security
Task #1
Mariam Abdelaty
CU2000406
*/

/*
A pid manager is a piece of software that is responsible for handling process identifiers.
It is responsible for the following points:
    1.Creating and assigning process identifiers to new processes.
    2.Releasing the process identifier when that process completes execution.
    3.Reassigning this process identifier to a newly created process.

Each created process identifier should be unique, meaning that no two processes identifiers
should have the identifiers. You are required to implement the following functions:
    ✓ int allocate map(void)—Creates and initializes a data structure for representing
    pids. This function returns -1 if unsuccessful, 1 if successful. You can use any
    data structure of your choice.
    ✓ int allocate pid(void)—Allocates and returns a pid. This function should return
    1 if unable to allocate a pid (all pids are in use).
    ✓ void release pid(int pid)—Releases a pid.
*/

//IMPORTS
#include<stdio.h> //standard input output
#include<stdlib.h> //standard library functions
#include<unistd.h> //unix standard
#include<sys/wait.h> //for waitpid...

//DEFINING CONSTRAINTS TO PROVIDE A RANGE OF POSSIBLE PID VALUES AND ALLOCATE THEM 
#define MIN_PID 300
#define MAX_PID 5000
#define ARRAY_SIZE MAX_PID-MIN_PID+1

//DEFINE VARIABLES FOR AVAILABILITY OF A PID, 0 = AVAILABLE AND 1 IS UNAVAILAIBLE
int available = 0;
int unAvailable = 1;

int PID_array[ARRAY_SIZE]; //an array is used to store or maintain the pid statuses

int allocate_map(void){
    //for loop used to initialize the array of pids, marking them as available
    for (int i = 0; i<ARRAY_SIZE;i++){
        PID_array[i] = available;
    }
    //for loop used to check if all the pid statuses have been allocated appropriately
    for (int i = 0; i<ARRAY_SIZE;i++){
        if(PID_array[i] != available){
            return -1; //unsuccessful
        };
    }
    return 1; //successful
}


int allocate_pid(void){
    for(int i = 0; i<ARRAY_SIZE;i++){
        if(PID_array[i] == available){ //check pid availability
            PID_array[i] = unAvailable; //make pid unavailable 
            return i+300; // add 300 because min pid is 300
        }
    }
    return 1; //if none are free 1 is returned
}


int release_pid(int p){
    int pid = p - 300; //subtract 300 to get the index 
    PID_array[pid] = 0; //make the pid available again
}

int main(){
    allocate_map();
    allocate_pid();
    allocate_pid();

    int s = 0;
    printf("\n-----------------TESTING------------------\n\n");
    for (int i = 0; i<ARRAY_SIZE; i++){
        if(PID_array[i] == 1){
            printf("[%d] = %d\t", i+300, PID_array[i]);
            s++;
        }
    }
    printf("\n\nNumber of PIDs in Use: %d\n", s);
    printf("\n----------------END TESTING-----------------\n\n");

    return 0;
}