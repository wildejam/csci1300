// CSCI1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 5 - Problem #2

#include <iostream>
#include <iomanip>

using namespace std;


/*
stats(): Takes in an array of doubles and its size, and prints the minimium value, product, and average of the elements to 3 digit precision.
Parameters:
array[] - The array of doubles to be processed
arraySize - The size of the array that is passed in
Returns: Nothing
*/
void stats(double array[], int arraySize) {
    // Initialize variables; set product = 1 to properly begin the product calculation loop
    double min = 0;
    double product = 1;
    double sum = 0;
    double average = 0;

    // Find the minimum value in the array
    for (int i = 0; i < arraySize; i++) {
        // If the loop is running for the first time, initialize min with the first value of the array
        if (i == 0) {
            min = array[0];
        }
        if (array[i] < min) {
            min = array[i];
        }
    }

    // Find the product of all of the elements
    for (int i = 0; i < arraySize; i++) {
        product = product * array[i];
    }

    // Find the average of all of the elements
    // Calculate the sum...
    for (int i = 0; i < arraySize; i++) {
        sum = sum + array[i];
    }
    // ...and divide it by the number of elements there are
    average = sum / arraySize;

    
    // Print the calculated statistics of array[], at 3 digit precision
    cout << fixed << setprecision(3) << "Min: " << min << endl;
    cout << fixed << setprecision(3) << "Product: " << product << endl;
    cout << fixed << setprecision(3) << "Avg: " << average << endl;
}

// Main function for testing stats()
int main() {
    double array[] = {1.24, 5.68, 3.456};
    int arraySize = 3;

    stats(array, arraySize);

    return 0;
}