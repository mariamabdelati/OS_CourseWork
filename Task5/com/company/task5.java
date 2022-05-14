/*
KH5004CEM Operating Systems and Security
Task #5
Mariam Abdelaty
CU2000406
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
    public int npoints = 0; // number of points to be generated
    public int hit_count = 0; // keeps track of the points that where generated that lie within the circle

    /**
     * This method is used to generate a random double which is later used to generate
     * the number of points specified
     * @returns random double
     */
    public static double random_double(){
        Random rand = new Random();
        return rand.nextDouble();
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
    public void calculateCirclePoints(){
        //Check for points inside circle
        for (int i = 0; i < npoints; i++){
            // Generate points in a square of side 2 units, from -1 to 1 exclusive.
            double x = random_double() * 2.0 - 1.0;
            double y = random_double() * 2.0 - 1.0;

            // calculate the distance
            double pt_distance = x*x + y*y;
            // if the distance is less than 1, the point lies inside the circle
            if (pt_distance < 1.0){
                hit_count++;
            }
        }
    }

    /**
     * This method is used to calculate the value of pi
     * using the formula specified by the problem statement
     * 4 * number of points in the circle (hit count) / total number of points (npoints)
     * @returns approximated value of pi
     */
    public double calculatePi(){
        return 4.0 * hit_count / npoints;
    }
}

class GeneratePoints extends Thread {
    CirclePoints obj;
    public GeneratePoints(CirclePoints x){
        obj = x;
    }


    /**
     * This method is used to run the point generation thread to generate
     * random points and determine the hit count (points lying within the circle)
     * using the method defined for the object of type circlePoints
     */
    public void run() {
        obj.calculateCirclePoints();
        System.out.println("The number of points generated within " +
                "the circle using Thread 1 is: " + obj.hit_count);
    }
}

public class task5 {
    /**
     * This is the main method which makes use of the GeneratePoints Class
     * defined earlier. The desired number of points to be generated is passed
     * as a commandline argument. The number is set in the global variable {npoints}
     * for the CirclePoints obj.
     * The program waits for the generate points thread to complete in order
     * to calculate the value of pi.
     * The program prints the value of pi
     * @param args represents the number of points to be generated.
     *             If no param is provided or more than 1 argument is passed, the program exits.
     */
    public static void main(String[] args) {

        System.out.println("Welcome to Monte Carlo Program");

        if (args.length > 1){
            System.out.println("Too many command line arguments found. Only One Needed. Exiting Program.");
            System.exit(0);
        }
        else if (args.length < 1){
            System.out.println("No command line arguments found. Exiting Program.");
            System.exit(0);
        }
        else {
            //initalized an object that contains the variables to be used by the thread
            CirclePoints obj = new CirclePoints();

            //set the npoints to the user defined value
            try {
                obj.npoints = Integer.parseInt(args[0]);

            // exit the program if string cannot be parsed to int
            } catch (NumberFormatException e){
                System.out.println("The input type cannot be parsed to integer. Please enter a valid number.");
                System.exit(0);
            }
            System.out.println("Number of points to be generated is: " + obj.npoints);


            //  create thread one object to generate the points
            GeneratePoints t1 = new GeneratePoints(obj);

            System.out.println("**Starting Thread 1... Generating Points...**");
            // starting thread one
            t1.start();

            try {
                // wait for thread one to finish before calculating the value of pi
                System.out.println("Waiting for Thread 1 to complete before calculating pi...");
                t1.join();

            } catch(InterruptedException e){
                System.out.println(e);
            }
            // calculate pi value and print it
            System.out.println("The approximate value of pi for the desired amount of points is: " + obj.calculatePi());
        }
    }
}