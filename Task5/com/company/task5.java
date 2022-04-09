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

package Task5.com.company;
import java.util.Random;
import java.util.Scanner;


class CirclePoints {
    //Generates a double precision random number
    public static int npoints = 0; // number of points to be generated
    public static int hit_count = 0; // keeps track of the points that where generated that lie within the circle
    // initialize random number
    public synchronized static double random_double(){
        Random rand = new Random();
        double random_doub = rand.nextDouble();
        return random_doub;
    }

    // calculates the value of pi
    public synchronized static double calculate(){
        double points = 4.0 * hit_count;
        return points / npoints;
    }
}

class GeneratePoints extends Thread {
    CirclePoints t;
    public GeneratePoints(CirclePoints x){
        t = x;
    }
    public void run() {
        //Check for points inside circle
        for (int i = 0; i < CirclePoints.npoints; i++){
            //generate random numbers between -1.0 and 1.0 (exclusive)
            double x = CirclePoints.random_double() * 2.0 - 1.0;
            double y = CirclePoints.random_double() * 2.0 - 1.0;

            if (Math.sqrt(x*x + y*y) < 1.0){
                CirclePoints.hit_count++;
            }
        }

        System.out.println("The number of points generated using Thread 1 within the circle is: " + CirclePoints.hit_count);
    }
}

class CalculatePi extends Thread {
    CirclePoints t;
    public CalculatePi(CirclePoints x){
        t = x;
    }

    public void run() {
        System.out.println("The approximate value of pi for the desired amount of points is: " + CirclePoints.calculate());
    }
}

public class task5 {
    public static void main(String[] args) {
        System.out.println("Initializing Threaded Monte Carlo Program");
        Scanner reader = new Scanner(System.in);  // Reading from System.in
        System.out.print("Enter the desired number to generate for the Monte Carlo program: ");
        int n = reader.nextInt(); // Scans the next token of the input as an int.
        //once finished
        reader.close();
        //initalized an object that contains the variables to be used by the threads
        CirclePoints ob = new CirclePoints();
        //set the npoints to the user defined value
        CirclePoints.npoints = n;
        System.out.println("Number of points to be generated is: " + CirclePoints.npoints);

        //  create thread one object to generate the points
        GeneratePoints t1 = new GeneratePoints(ob);
        System.out.println("**Starting Thread 1... Generating Points...**");
        // starting thread one
        t1.start();
        try {
            // wait for thread one to finish before running thread 2
            System.out.println("Waiting for Thread 1 to complete before running Thread 2...");
            t1.join();
        } catch(InterruptedException e){
            System.out.println(e);
        }

        // create thread two object that takes the object after thread one has completed and calculates the value of pi
        CalculatePi t2 = new CalculatePi(ob);
        System.out.println("**Starting Thread 2... Calculating Pi...**");
        t2.start();
    }
}
