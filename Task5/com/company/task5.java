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

/**
 * <h1>MonteCarlo Technique Multithreaded Program</h1>
 * The program implements threads to calculate the approximate
 * value of pi
 * <p>
 * <b>Note:</b> The program is to be run from the commandline passing
 * arguments in a similar format to: java com.company.Main 80000
 *
 * @author  Mariam Abdelati
 * @since   2022-04-08
 */

class CirclePoints {
    // define the global variables to be shared by the threads running on the CirclePoints ob
    public static int npoints = 0; // number of points to be generated
    public static int hit_count = 0; // keeps track of the points that where generated that lie within the circle

    /**
     * This method is used to generate a random double which is later used to generate
     * the number of points specified
     * @returns random double
     */
    public synchronized static double random_double(){
        Random rand = new Random();
        double random_doub = rand.nextDouble();
        return random_doub;
    }

    /**
     * This method is used to calculate the value of pi
     * using the the formula specified by the monte carlo
     * technique 4 * number of points in the circle (hit count) / total number of points (npoints)
     * @returns approximated value of pi
     */
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

    /**
     * This method is used to generate random points for the specified number of points
     * The method makes use of the random method and generates two points within the square
     * The general rule of unit circle is applied where if the coordinates of the circle
     * lie at the origin (0,0), the distance of any 2 points inside the circle must
     * be less than one (radius). Thus, if the condition is met then the  points lie
     * within the circle
     * The global variable {hit_count} is incremented if the value lies in the circle
     */
    public void run() {
        //Check for points inside circle
        for (int i = 0; i < CirclePoints.npoints; i++){
            // Generate points in a square of side 2 units, from -1 to 1.
            double x = CirclePoints.random_double() * 2.0 - 1.0;
            double y = CirclePoints.random_double() * 2.0 - 1.0;

            // calculate the distance 
            double pt_distance = x*x + y*y;
            // if the distance is 1 or less then the point lies on the circle
            if (pt_distance <= 1.0){
                CirclePoints.hit_count++;
            }
        }

        System.out.println("The number of points generated within the circle using Thread 1 is: " + CirclePoints.hit_count);
    }
}

public class task5 {
    /**
     * This is the main method which makes use of the GeneratePoints Class
     * defined earlier. First the user inputs the desired number of points
     * to be generated. The number is set in the global variable {npoints}
     * for the CirclePoints ob.
     * The program waits for the generate points thread to complete in order
     * to calculate the value of pi.
     * The program prints the value of pi
     * @param args represents the number of points to be generated.
     *             If no param is provided or more than 1 argument is passed, the program exits.  
     */
    public static void main(String[] args) {

        System.out.println("Welcome to Monte Carlo Program");

        if (args.length == 1) {
            //initalize an object that contains the variables to be used by the threads
            CirclePoints ob = new CirclePoints();

            //set the npoints to the user defined value
            CirclePoints.npoints = Integer.valueOf(args[0]);
            System.out.println("Number of points to be generated is: " + CirclePoints.npoints);

            //  create thread one object to generate the points
            GeneratePoints t1 = new GeneratePoints(ob);
            System.out.println("**Starting Thread 1... Generating Points...**");
            // starting thread one
            t1.start();
            try {
                // wait for thread one to finish before running thread 2
                System.out.println("Waiting for Thread 1 to complete before calculating pi...");
                t1.join();
            } catch(InterruptedException e){
                System.out.println(e);
            }

            // calculate pi value and print it
            System.out.println("The approximate value of pi for the desired amount of points is: " + CirclePoints.calculate());
        } else if (args.length > 1){
            System.out.println("Too many command line arguments found. Only One Needed. Exiting Program.");
            System.exit(0);
        }
        else{
            System.out.println("No command line arguments found. Exiting Program.");
            System.exit(0);
        }
    }
}
