/*
KH5004CEM Operating Systems and Security
Task #5
Mariam Abdelaty
CU2000406
*/

/*
    Create a multithreaded program to calculate the value of π using MonteCarlo
technique. This technique works as follows: Suppose you have a circle inscribed within a
square, as shown in the Figure.

Assume that the radius of this circle is 1. First, generate a series of random points as simple (x,
y) coordinates. These points must fall within the Cartesian coordinates that bound the square.
Of the total number of random points that are generated, some will occur within the circle.
Next, estimate π by noticing that the area of the square is (2𝑟)2 = 4𝑟2 and the area of the circle
is πr2, so this means that:
    𝐴𝑟𝑒𝑎 𝑜𝑓 𝑐𝑖𝑟𝑐𝑙𝑒 / 𝐴𝑟𝑒𝑎 𝑜𝑓 𝑠𝑞𝑢𝑎𝑟𝑒 = 𝑛𝑢𝑚𝑏𝑒𝑟 𝑜𝑓 𝑝𝑜𝑖𝑛𝑡𝑠 𝑖𝑛 𝑐𝑖𝑟𝑐𝑙𝑒 / 𝑡𝑜𝑡𝑎𝑙 𝑛𝑢𝑚𝑏𝑒𝑟 𝑜𝑓 𝑝𝑜𝑖𝑛𝑡𝑠 = πr2 / 4𝑟2
    
Hence π can be estimated as :
    π= 4× (number of points in circle) / (total number of points)

Hint: You need to create a separate thread that is responsible of generating a number of
random points. The thread will count the number of points that occur within the circle and
assign that result to a global variable. When this thread has finished, the parent thread will
calculate and output the estimated value of π. What will happen when we increase the
number of generated points? Justify your answer.
*/