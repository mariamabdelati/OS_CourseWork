/*
KH5004CEM Operating Systems and Security
Task #6: Paging
Mariam Abdelaty
CU2000406
*/

#include <stdlib.h>
#include <stdio.h>

// define a constant page size of 4-KB as specified
#define PAGE_SIZE 4096

int main(int argc, char *argv[]) {

    // declare unsigned integers since the addresses can never be negative (32-bit)
    unsigned int address;
    unsigned int page_number;
    unsigned int offset;

    // if less than 1 parameter are passed, the virtual address is missing 
    if (argc < 2){
        printf("At least 1 parameter is needed\n");
        exit(1);
    }

    // convert the string passed on command line to integer and  save it to address
    address = atoi(argv[1]);

    // the page number is equivalent to the address divided by the page size of 4-KB
    page_number = address / PAGE_SIZE;

    // the offset is equivalent to remainder of dividing the address by the page size of 4-KB
    offset = address % PAGE_SIZE;

    printf("The address %u contains: \n  page number = %u\n  offset = %u\n", address, page_number, offset);

    return 0;
}