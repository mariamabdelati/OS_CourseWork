## OS CourseWork

<p align="center" name="top"> </p>

*Portfolio -- University Junior Year*
##### Mariam Abdelati

### Table of Contents

- [Task One](#taskone)
- [Task Two](#tasktwo)
- [Task Three](#taskthree)
- [Task Four](#taskfour)
- [Task Five](#taskfive)
- [Task Six](#tasksix)


### Task One <a id='taskone'></a>
A pid manager is a piece of software that is responsible for handling process identifiers. It is responsible for the following points: 

<ol>
<li> Creating and assigning process identifiers to new processes. </li>
<li> Releasing the process identifier when that process completes execution.  </li>
<li> Reassigning this process identifier to a newly created process.  </li>
</ol>

Each created process identifier should be unique, meaning that no two processes identifiers should have the identifiers. You are required to implement the following functions: 
<ul>
<li> int allocate map(void)—Creates and initializes a data structure for representing pids. This function returns -1 if unsuccessful, 1 if successful. You can use any data structure of your choice. </li>
<li> int allocate pid(void)—Allocates and returns a pid. This function should return 1 if unable to allocate a pid (all pids are in use).</li>
<li> void release pid(int pid)—Releases a pid.</li>
</ul>


----
### Task Two <a id='tasktwo'></a>

One of the first IPC mechanisms in early UNIX systems were Pipes. Pipes acts as a conduit allowing two processes to communicate, they typically provide one of the simpler ways for processes to communicate with one another. Ordinary pipes are the most common type of pipes. Ordinary pipes allow two processes to communicate in standard producer– consumer fashion: the producer writes to one end of the pipe (the write-end) and the consumer reads from the other end (the read-end). As a result, ordinary pipes are unidirectional, allowing only one-way communication. If two-way communication is required, two pipes must be used, with each pipe sending data in a different direction. Design a program using ordinary pipes such that one process sends a string message to the second process. The second process should then reverse the <u>**case**</u> of each character in the message and sends it back to the first process. As an example, if the first process sends the message *Hi There*, the second process will return *hI tHERE*. This will require using two pipes, one for sending the original message from the first to the second process and the other for sending the modified message from the second to the first process.

----
### Task Three <a id='taskthree'></a>

Create a file-copying program named filecopy using ordinary pipes. This program should receive two parameters: 

<ol>
<li> The name of the file to be copied </li>
<li> The name of the copied file</li>
</ol>
<p>
The program then must create an ordinary pipe and write the contents of the file required to be copied to the pipe. The child process should then read this file from the pipe and write it to the destination file. For example, if we invoke the program as follows: <br>
filecopy file_to_be_copied.txt copy.txt <br>
The <b>file file_to_be_copied.txt</b> will be written to the pipe. The child process will read the contents of this file and write it to the destination file <b>copy.txt</b>.

----
### Task Four <a id='taskfour'></a>

Create a multithreaded software that calculates may statistical parameters for a list of numbers. This program will receive a series of numbers on the command line and then creates a five separate worker threads. One thread will determine the average of the numbers, the second will determine the maximum value, and the third will determine the minimum value, the fourth will determine their median and the fifth will determine their standard deviation. As an example, suppose your program is passed the following series of integers: <br>
80 72 11 25 59 82 99 <br>

The program should output: 
<ul>
<li> The average value is 61.14</li>
<li> The minimum value is 11 </li>
<li> The maximum value is 99 </li>
<li>  The median value is 72 </li>
<li>  The standard deviation value is 29.68 </li>
</ul>
 The variables representing the average, minimum, maximum, median and standard deviation values will be stored globally. The worker threads will set these values, and the parent thread will output the values once the workers have exited.

----
### Task Five <a id='taskfive'></a>

Create a multithreaded program to calculate the value of π using <b><i>MonteCarlo</i> </b>technique. This technique works as follows: Suppose you have a circle inscribed within a square, as shown in the below Figure: <br>

<img src="https://i.postimg.cc/K8Np680L/monte-carlo.png" alt="MonteCarlo Technique" width=“1000”>
<br>
<br>

Assume that the radius of this circle is 1. First, generate a series of random points as simple (x, y) coordinates. These points must fall within the Cartesian coordinates that bound the square. Of the total number of random points that are generated, some will occur within the circle. Next, estimate π by noticing that the area of the square is (2𝑟)² = 4𝑟² and the area of the circle is πr² , so this means that: <br>
𝐴𝑟𝑒𝑎 𝑜𝑓 𝑐𝑖𝑟𝑐𝑙𝑒 / 𝐴𝑟𝑒𝑎 𝑜𝑓 𝑠𝑞𝑢𝑎𝑟𝑒 = 𝑛𝑢𝑚𝑏𝑒𝑟 𝑜𝑓 𝑝𝑜𝑖𝑛𝑡𝑠 𝑖𝑛 𝑐𝑖𝑟𝑐𝑙𝑒 / 𝑡𝑜𝑡𝑎𝑙 𝑛𝑢𝑚𝑏𝑒𝑟 𝑜𝑓 𝑝𝑜𝑖𝑛𝑡𝑠 = πr² / 4𝑟² <br>

Hence π can be estimated as: <br>
π= 4× (number of points in circle) / (total number of points) <br>

Hint: You need to create a separate thread that is responsible of generating a number of random points. The thread will count the number of points that occur within the circle and assign that result to a global variable. When this thread has finished, the parent thread will calculate and output the estimated value of π. What will happen when we increase the number of generated points? Justify your answer

----
### Task Six <a id='tasksix'></a>

Assume that for a certain system, it has a 32-bit virtual address with a 4-KB page size. Write a program that takes a virtual address (in decimal) on the command line and outputs the page number and offset for that given address. For example, if we input 19986 to the program, the output would be: <br>
The address 19986 contains: <br>
&emsp; page number = 4 <br>
&emsp; offset = 3602 <br>
You should use an appropriate data type to store 32 bits. Also, it will be a good idea to use unsigned data types as well.

----
<p align="center">
  <a href="#top">Back to Top</a>
</p>
