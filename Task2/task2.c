/*
KH5004CEM Operating Systems and Security
Task #2: Process Communication using Ordinary Pipes
Mariam Abdelaty
CU2000406
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/wait.h>


int main(){

    // Since the processes need to communicate back and forth, two pipes are needed

    /*
     integer arrays for the file descriptors of the pipe for each pipe are declared.
     fd[1] is used for the writing end and fd[0] is used for the reading end
    */
    int fd_1[2];
    int fd_2[2];

    // return value one and two are used later during pipe creation. If -1 is returned an error occurred during creation
    int return_value_1, return_value_2;
    // rc is used to store the return value of the fork function
    int rc;

    // bytes_read is used to stored the return value of getline, if it is -1, then an error occurred during reading
    int bytes_read;

    // char pointer used to store input from the user in getline
    char *pipe1message;

    // the size of the string to be read from the user
    size_t message_size = 100;

    // readmessage is used to store the message communicated between the pipes 
    char readmessage[100];

    // pipe2message is used to store the altered message and writing it into pipe
    char pipe2message[100];

    // allocate memory of size 100 to store pipe1message
    pipe1message = (char *) malloc (message_size);


    printf("Enter a string message: ");

    // get user input, getline gets all inout from user including spaces
    bytes_read = getline(&pipe1message, &message_size, stdin);

    // exit the program if an error occurs in reading
    if (bytes_read == -1){
        printf("An error occurred during input.\n");
        exit(1);
    } 

    // exit the prgram if the user provides no input
    if(*pipe1message == '\n'){
        printf("No input was supplied.\n");
        exit(1);
    }

    // construct the first pipe and save its return value
    return_value_1 = pipe(fd_1);
    
    // if an error occured during pipe construction exit the program
    if (return_value_1 == -1){
        printf("Unable to create pipe 1 \n");
        exit(1);
    }

    // create second pipe
    return_value_2 = pipe(fd_2);

    if (return_value_2 == -1){
        printf("Unable to create pipe 2 \n");
        exit(1);
    }

    // create child process
    rc = fork();

    if (rc < 0) {
        printf("Unable to fork \n");
        exit(1);
    } else if (rc > 0) {

        // close the unwanted read side of pipe 1
        close(fd_1[0]);
        // close the unwanted write side of pipe 2
        close(fd_2[1]);

        printf("The parent writes message 1 into pipe 1...\n");

        // parent write the message into pipe 1, so the child can read it
        write(fd_1[1], pipe1message, 100);

        // parent reads the message from pipe 2 which child has sent
        read(fd_2[0], readmessage, 100);

        printf("Parent: reading from pipe 2... The Message recieved is: %s\n", readmessage);
        
        // parent waits till the child is done executing
        wait(NULL);
    } else {

        // close the unwanted write side of pipe 1
        close(fd_1[1]);

        // close the unwanted read side of pipe 2
        close(fd_2[0]);

        // child reads the message that the parent wrote into pipe 1
        read(fd_1[0], readmessage, 100);

        printf("Child: reading from pipe 1... The Message recieved is: %s\n", readmessage);

        printf("The child alters the message read and saves it into message 2 and writes message 2 into pipe 2... \n");

        // for loop iterates of the characters of the string in the read message
        for(int i = 0;i<strlen(readmessage);i++){

            /* 
              if the ASCII int representing the character is between 65 and 90, then the character is uppercase
              32 is added to the integer to convert it to lowercase then it is cast back into a char
            */
	        if((int)readmessage[i]>=65 && (int)readmessage[i]<=90){
			    pipe2message[i]=(int)readmessage[i]+32;

            /*
              if the ASCII int representing the char is between 97 and 122, then it is lower case
              32 is subtracted from the integer to convert it to uppercase then it is cast back to char
            */    
		    } else if((int)readmessage[i]>=97 && (int)readmessage[i]<=122){
			    pipe2message[i]=(int)readmessage[i]-32;

            // otherwise the character is not an alphabet so keep it as it is 
		    } else {
                pipe2message[i]=(int)readmessage[i];
            }
	    }

        // write the altered message into pipe 2
        write(fd_2[1], pipe2message, 100);
    }
    
    return 0;
}