/*
KH5004CEM Operating Systems and Security
Task #3
Mariam Abdelaty
CU2000406
*/

/*
    Create a file-copying program named filecopy using ordinary pipes. This program should
receive two parameters:
    1.The name of the file to be copied
    2.The name of the copied file

    The program then must create an ordinary pipe and write the contents of the file required to
be copied to the pipe. The child process should then read this file from the pipe and write it to
the destination file. For example, if we invoke the program as follows:
        filecopy file_to_be_copied.txt copy.txt
The file file_to_be_copied.txt will be written to the pipe. The child process will read the
contents of this file and write it to the destination file copy.txt.
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include <sys/wait.h>


int main(int argc, char * argv[]){

    
    /*
     integer array for the file descriptors of the pipe for each pipe are declared.
     fd[1] is used for the writing end and fd[0] is used for the reading end
    */
    int fd[2];

    // return value is used later during pipe creation. If -1 is returned an error occurred during creation
    int return_value;
    // rc is used to store the return value of the fork function
    int rc;

    // readbuffer is used to store the content of the file read
    char readbuffer[100];

    // pipe2message is used to store the altered message and writing it into pipe
    //char writebuffer[100];

    // readLines is used to save the return from reading the file. If it is 0 then the end of the file has been reached
    int readLines;

    // if less than 2 parameters are passed, one of the file names are missing 
    if (argc < 3){
        printf("At least 2 parameters are needed");
        exit(1);
    }

    // construct the pipe and save its return value
    return_value = pipe(fd);

    // if an error occured during pipe construction exit  the program
    if (return_value == -1){
        printf("Unable to create pipe 1 \n");
        exit(1);
    }

    // readFile saves the return of open the file to be read with read permission. If -1 is returned an error occurred during opening 
    int readFile = open(argv[1], O_RDONLY);

    // writeFile saves the return of open the file to be written into with write permission. If -1 is returned an error occurred during opening
    int writeFile = open(argv[2], O_WRONLY);

    // if opening the files fails, display and error and exit
    if (readFile == -1 || writeFile == -1){
        printf("Error opening files \n");
        exit(1);
    }

    // create child process
    rc = fork();

    if (rc < 0) {
        printf("Unable to fork \n");
        exit(1);
    } else if (rc > 0) {

        // close the unwanted read side of pipe
        close(fd[0]);
            
        printf("The parent writes file contents into pipe...\n");

        while ( (readLines = read(readFile, readbuffer, sizeof(readbuffer))) > 0){
        // parent write the message into pipe, so the child can read it
        write(fd[1], readbuffer, readLines);
        }
        close(fd[1]);
        // parent waits till the child is done executing
        wait(NULL);
    } else {

        // close the unwanted write side of pipe
        close(fd[1]);

        // child reads the content that the parent wrote into pipe
        int readLines_2 = read(fd[0], readbuffer, sizeof(readbuffer));

        //prints extra characters from pipe (not sure how to fix)
        printf("Child: reading from pipe... The content recieved is %s\n", readbuffer); 

        printf("The child writes content into target file... \n");
 
        // write the content into file 2
        write(writeFile, readbuffer, readLines_2);
    }

    return 0;
}