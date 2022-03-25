/*
KH5004CEM Operating Systems and Security
Task #4
Mariam Abdelaty
CU2000406
*/

/*
    Create a multithreaded software that calculates may statistical parameters for a list of
numbers. This program will receive a series of numbers on the command line and then creates
a five separate worker threads. One thread will determine the average of the numbers, the
second will determine the maximum value, and the third will determine the minimum value,
the fourth will determine their median and the fifth will determine their standard deviation. As
an example, suppose your program is passed the following series of integers:
        80 72 11 25 59 82 99
The program should output:
    - The average value is 61.14
    - The minimum value is 11
    - The maximum value is 99
    - The median value is 72
    - The standard deviation value is 29.68
The variables representing the average, minimum, maximum, median and standard deviation
values will be stored globally. The worker threads will set these values, and the parent thread
will output the values once the workers have exited
*/