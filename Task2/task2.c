/*
KH5004CEM Operating Systems and Security
Task #2
Mariam Abdelaty
CU2000406
*/

/*
    One of the first IPC mechanisms in early UNIX systems were Pipes. Pipes acts as a
conduit allowing two processes to communicate, they typically provide one of the simpler ways
for processes to communicate with one another. Ordinary pipes are the most common type of
pipes. Ordinary pipes allow two processes to communicate in standard producer– consumer
fashion: the producer writes to one end of the pipe (the write-end) and the consumer reads
from the other end (the read-end). As a result, ordinary pipes are unidirectional, allowing only
one-way communication. If two-way communication is required, two pipes must be used, with
each pipe sending data in a different direction. 

    Design a program using ordinary pipes such that
one process sends a string message to the second process. The second process should then
reverse the case of each character in the message and sends it back to the first process. As an
example, if the first process sends the message Hi There, the second process will return hI
tHERE. This will require using two pipes, one for sending the original message from the first to
the second process and the other for sending the modified message from the second to the
first process
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
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

    printf("Enter a string message: ");

    // allocate memory of size 100 to store pipe1message
    pipe1message = (char *) malloc (message_size);

    // get user input, getline gets all inout from user including spaces
    bytes_read = getline(&pipe1message, &message_size, stdin);

    if (bytes_read == -1){
        printf("An error occurred during input.");
        exit(1);
    } else {

        // construct the first pipe and save its return value
        return_value_1 = pipe(fd_1);

        // if an error occured during pipe construction exit  the program
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

            printf("Parent: reading from pipe 2... The Message recieved is %s\n", readmessage);

            // parent waits till the child is done executing
            wait(NULL);
        } else {

            // close the unwanted write side of pipe 1
            close(fd_1[1]);

            // close the unwanted read side of pipe 2
            close(fd_2[0]);

            // child reads the message that the parent wrote into pipe 1
            read(fd_1[0], readmessage, 100);

            printf("Child: reading from pipe 1... The Message recieved is %s\n", readmessage);

            printf("The child alters the message read and saves it into message 2 and writes message 2 into pipe 2... \n");

            int i = 0;
            // for loop iterates of the characters of the string in the read message
            for(i = 0;i<strlen(readmessage);i++){
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
    }

    return 0;
}