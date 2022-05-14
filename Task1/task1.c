/*
KH5004CEM Operating Systems and Security
Task #1: PID manager
Mariam Abdelaty
CU2000406
*/

//IMPORTS
#include<stdio.h> //standard input output

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


void release_pid(int p){
    // check if the pid supplied is a valid pid
    if (p > MAX_PID || p < MIN_PID){
        printf("No PID was released since PID does not exist.\n");
        return;
    }

    int pid = p - 300; //subtract 300 to get the index

    // check if the pid is already made available
    if (PID_array[pid] == available){
        printf("No PID was released since PID is already available.\n");
        return;
    }

    PID_array[pid] = available; //make the pid available again
    printf("PID released: %d\n", p); // display the released pid
}

int main(){
    printf("\nWelcome to PID Manager Program\n\n");
    printf("\n-----------------TESTING------------------\n\n");

    printf("\n**Testing Map Allocation function...\n");
    //map_allocated is used to save the return value of the allocate_function
    int map_allocated = allocate_map();
    
    /*
        if the return value is 1, then the data structure (array) used was successful
        otherwise, the map allocation was unsuccessful
    */

    if (map_allocated == 1){
        printf("Map Allocation: Successful\n\n");
    } else {
        printf("Map Allocation: Unsuccessful\n");
    }

    printf("\n**Testing PID Allocation function...\n");

    //for loop is used to allocate 2 pids to test if the function words
    for (int i = 0; i < 2; i++){

        // pid_allocated variable is used to keep track of the return value of allocate_pid function
        int pid_allocated = allocate_pid();

        /*
         if the return value is 1, then the pid's have not been allocated since all pid's are in use
         otherwise, the pid is returned and alloctaion was successful.
        */
        if (pid_allocated == 1){
            printf("All PIDs are currently in use. PID Allocation: Unsuccessful\n\n");
        } else {
            printf("PID Allocation: Successful\n");
        }
    }

    printf("\nPrinting PIDs Allocated...\n");
    //int s is used to keep track of the number of pids allocated 
    int s = 0;
    //for loop iterates over the array and checks the pid status
    for (int i = 0; i<ARRAY_SIZE; i++){
        // if the PID is unavailable (==1), then it is printed with its status
        if(PID_array[i] == unAvailable){
            printf("[%d] = %d\t", i+300, PID_array[i]);
            s++;
        }
    }
    printf("\n\nNumber of PIDs in Use: %d\n", s);

    printf("\n**Testing Release PID function...\n");
    int pid = 301; // valid pid
    int pid1 = 5001; // a pid out of upper range
    int pid2 = 299; // pid out of lower range
    int pid3 = 4000; // pid that is already available

    // run the release function on pid variable
    printf("\n**Testing with PID %d...\n", pid);
    release_pid(pid);

    printf("\n**Testing with PID %d...\n", pid1);
    release_pid(pid1);

    printf("\n**Testing with PID %d...\n", pid2);
    release_pid(pid2);

    printf("\n**Testing with PID %d...\n", pid3);
    release_pid(pid3);

    printf("\nPrinting PIDs Allocated After Release...\n");
    //int w is used to keep track of the number of pids allocated 
    int w = 0;
    //for loop iterates over the array and checks the pid status
    for (int i = 0; i<ARRAY_SIZE; i++){
        // if the PID is unavailable (==1), then it is printed with its status
        if(PID_array[i] == unAvailable){
            printf("[%d] = %d\t", i+300, PID_array[i]);
            w++;
        }
    }
    printf("\n\nNumber of PIDs in Use After Release: %d\n", w);

    printf("\n**Testing Unsuccessful case in PID function...\n");


    printf("\nAllocating All PIDs...\n");
    for (int i = 0; i<ARRAY_SIZE; i++){
        // pid_allocated variable is used to keep track of the return value of allocate_pid function
        int pid_allocated = allocate_pid();
        /*
         if the return value is 1, then the pid's have not been allocated since all pid's are in use
         otherwise, the pid is returned and allocatation was successful.
        */
        if (pid_allocated == 1){
            printf("***Unsuccessful Case Reached***\n");
            printf("All PIDs are currently in use. PID Allocation: Unsuccessful\n");
        }
    }
    
    int p = 0;
    //for loop iterates over the array and checks the pid status
    for (int i = 0; i<ARRAY_SIZE; i++){
        // if the PID is unavailable (==1), counter is incremented
        if(PID_array[i] == unAvailable){
            p++;
        }
    }

    printf("\n\nNumber of PIDs in Use: %d\n", p);

    printf("\n----------------TESTING COMPLETED-----------------\n\n");
 
    return 0;
}