// CSCI1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 5 - Problem #4

#include <iostream>

using namespace std;

/*
maxProd(): Takes in a 2D integer array with 10 columns, and returns the product of the maximum values from each row.
Parameters:
    arr[] - The 2D integer array with 10 columns to be processed
    rows - The number of rows that arr has
Returns: product - The product of each maximum value in each row
*/
int maxProd(int arr[][10], int rows) {
    // Initialize variables. Initialize product with 1 because of multiplication, and maxValue with the first value of the array
    int product = 1;
    int maxValue = arr[0][0];

    // Traverse each row...
    for (int i = 0; i < rows; i++) {
        // ...And for each column within the row...
        for (int j = 0; j < 10; j++) {
            // ...If the current value in the row is greater than the current maxValue for that row, set maxValue to that number.
            if (arr[i][j] > maxValue) {
                maxValue = arr[i][j];
            }
        }
        // After the maxValue of the row is found, multiply it by the product, and reset maxValue for the next row.
        product = product * maxValue;
        maxValue = arr[i + 1][0];
    }

    // Return the product when finished
    return product;
}

// Main function used for testing
int main() {
    int rows = 2;
    const int COLUMNS = 10;
    int array[rows][COLUMNS] = 
    {
        {9,2,2,3,5,7,8,7,6,8},
        {6,8,3,9,0,2,3,3,10,6}
    };

    cout << maxProd(array, rows) << endl;
    return 0;
}