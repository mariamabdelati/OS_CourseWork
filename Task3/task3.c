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