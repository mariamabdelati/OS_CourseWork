/*
KH5004CEM Operating Systems and Security
Task #4
Mariam Abdelaty
CU2000406
*/

package Task4.com.company;

import java.util.ArrayList;
import java.util.Collections;

/**
 * <h1>Statistical Calculator Program</h1>
 * The program implements threads to calculate the average,
 * minimum value, maximum value, median value, standard deviation
 * value and prints the output on the screen.
 * <p>
 * <b>Note:</b> The program is to be run from the commandline passing
 * arguments in a similar format to: java com.company.Main 80 72 11 25 59 82 99
 *
 * @author  Mariam Abdelati
 * @since   2022-04-09
 */

class Calculated {
    // define the global variables to be shared by the threads running on the Calculated obj
    public ArrayList<Integer> array = new ArrayList<>(); // holds the list of integeres inputted
    public double avg = 0.0; // holds the average value
    public int minValue = 0; // holds the min value
    public int maxValue = 0; // holds the max value
    public int medianValue = 0; // holds the median value
    public double stddev = 0; // holds the standard dev value

    /**
     * This method is used to calculate the average of the list elements
     * by calculating the sum of all elements in the list then dividing it by the total
     * The method sets the calculated value to the global variable {avg} of the class
     // @param param the array list taken from the commandline
     */
    public void average(){
        double sum = 0.0;

        for(int i = 0; i< array.size(); i++){
            sum += array.get(i);
        }
        avg = sum / (double)array.size();
    }

    /**
     * This method is used to find the minimum in the list elements supplied
     * by iterating through the list and comparing the value to the current minimum
     * The method sets the calculated value to the global variable {minValue} of the class
     //* @param param the array list taken from the commandline
     */
    public void minimum(){

        minValue = array.get(0);

        for(int i = 0; i< array.size(); i++){
            if (array.get(i) < minValue){
                minValue = array.get(i);
            }
        }
    }
    /**
     * This method is used to find the maximum in the list elements supplied
     * by iterating through the list and comparing the value to the current maximum
     * The method sets the calculated value to the global variable {maxValue} of the class
     //* @param param the array list taken from the commandline
     */
    public void maximum(){

        maxValue = array.get(0);

        for(int i = 0; i< array.size(); i++){
            if (array.get(i) > maxValue){
                maxValue = array.get(i);
            }
        }
    }

    /**
     * This method is used to find the median in the list elements supplied
     * by first sorting the arraylist then finding the midpoint and getting the value at that index
     * The method sets the calculated value to the global variable {medianValue} of the class
     //* @param param the array list taken from the commandline
     */
    public void median(){

        Collections.sort(array);

        int mid = array.size()/2;
        medianValue = array.get(mid);
    }

    /**
     * This method is used to find the standard deviation of the list elements supplied
     * by iterating through the list and finding the sum of squares of (deviation of each
     * value from the mean) then sets the standard deviation to the square root of the variance
     * (sum of squares over the array size)
     * The method sets the calculated value to the global variable {stddev} of the class
     //* @param param the array list taken from the commandline
     */
    public void strdev(){

        double temp = 0.0;
        for(int i = 0; i< array.size(); i++){
            temp = temp + Math.pow(array.get(i) - avg, 2);
        }
        stddev = Math.sqrt(temp / array.size());
    }
}

class AverageThread extends Thread {
    Calculated t;
    public AverageThread(Calculated x){
        t = x;
    }

    /**
     * This method is used to run the average thread to calculate the average
     * using the method defined for the object of type calculated
     */
    public void run() {
        System.out.println("\nSetting the Average...");
        t.average();
    }
}

class MinimumThread extends Thread {
    Calculated t;
    public MinimumThread(Calculated x){
        t = x;
    }

    /**
     * This method is used to run the minimum thread to find the minimum
     * using the method defined for the object of type calculated
     */
    public void run() {
        System.out.println("Setting the Minimum Value...");
        t.minimum();
    }
}

class MaximumThread extends Thread {
    Calculated t;
    public MaximumThread(Calculated x){
        t = x;
    }

    /**
     * This method is used to run the maximum thread to find the maximum
     * using the method defined for the object of type calculated
     */
    public void run() {
        System.out.println("Setting the Maximum Value...");
        t.maximum();
    }
}

class MedianThread extends Thread {
    Calculated t;
    public MedianThread(Calculated x){
        t = x;
    }

    /**
     * This method is used to run the median thread to find the median
     * using the method defined for the object of type calculated
     */
    public void run() {
        System.out.println("Setting the Median Value...");
        t.median();
    }
}

class StdDevThread extends Thread {
    Calculated t;
    public StdDevThread(Calculated x){
        t = x;
    }

    /**
     * This method is used to run the standard deviation thread to
     * calculate the standard deviation using the method defined for
     * the object of type calculated
     */
    public void run() {
        System.out.println("Setting the Standard Deviation Value...\n");
        t.strdev();
    }
}

public class task4 {
    /**
     * This is the main method which makes use of the Thread Classes
     * defined earlier. First the array elements are added to the global
     * arraylist as integers. The threads are run on the Calculated obj.
     * The standard deviation thread waits for the average thread in order
     * to run. The program waits for all the threads to complete then prints
     * the values calculated.
     * @param args represents the list of integers to be passed to the array.
     *             If no param is provided, the program exits.
     */
    public static void main(String[] args) {

        System.out.println("Welcome to Stats Calculator");

        //initalized an object that contains the variables to be used by the threads
        Calculated obj = new Calculated();

        // check if length of args array is greater than 0 so args have been supplied
        if (args.length > 0) {
            // iterate over the args and add to list as integers
            for (int i = 0; i < args.length; i++) {
                try {
                    obj.array.add(Integer.valueOf(args[i]));
                } catch (NumberFormatException e){
                    System.out.println("The input type cannot be parsed to integer. Please enter a valid number.");
                }
            }

            // print the array recieved to ensure correct input
            System.out.print("The Array received is: ");
            for ( int x : obj.array){
                System.out.print(x + " ");
            }

            // intialize the threads
            AverageThread t1 = new AverageThread(obj);
            MinimumThread t2 = new MinimumThread(obj);
            MaximumThread t3 = new MaximumThread(obj);
            MedianThread t4 = new MedianThread(obj);
            StdDevThread t5 = new StdDevThread(obj);

            // start the threads

            t1.start();

            t2.start();
            t3.start();
            t4.start();
            try {
                // wait for thread one to finish before running thread 5
                System.out.println("Waiting for Thread 1 (Average) to complete before running Thread 5 (Standard Dev)...");
                t1.join();
            } catch(InterruptedException e){
                System.out.println(e);
            }
            t5.start();

            try {
                // wait for all threads to complete to print output values
                System.out.println("Waiting for all threads to complete...");
                t2.join();
                t3.join();
                t4.join();
                t5.join();
            } catch(InterruptedException e){
                System.out.println(e);
            }
            System.out.println("The average value is: " + String.format("%.2f", obj.avg));
            System.out.println("The minimum value is: " + obj.minValue);
            System.out.println("The maximum value is: " + obj.maxValue);
            System.out.println("The median value is: " + obj.medianValue);
            System.out.println("The standard deviation value is: " + String.format("%.2f", obj.stddev));
        }
        else{
            System.out.println("No command line arguments found.");
            System.exit(0);
        }
    }
}