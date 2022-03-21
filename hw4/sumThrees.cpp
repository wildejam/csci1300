// CSCI1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 4 - Problem #1

// Problem: Take an input value, and compute the sum of all multiples of 3 between 0 and the value entered, inclusive

/* Algorithm:
    Initialize "endValue" integer variable and "sum" integer variable
    Prompt user for and get input for endValue
    If endValue >= 0,
        for an integer i=0, where i <= sum, with i increasing by 3 after each iteration,
            sum = sum + i
    Else if endValue < 0,
        Print "Invalid Input."
*/

#include <iostream>

using namespace std;

int main() {
    // Initialize input and output variables
    int sum = 0;
    int endValue = 0;

    // Prompt user for and recieve input
    cout << "Enter a positive integer: " << endl;
    cin >> endValue;

    // If input is a positive value, process input 
    if (endValue >= 0){

        // Add every multiple of 3 to the endValue until i reaches the "sum" value that the user inputted
        for (int i=0; i<=endValue; i=i+3){
            sum += i;
        }

        cout << "Sum: " << sum << endl;
    }

    // If input is negative, or is otherwise not valid, print "Invalid input."
    else {
        cout << "Invalid input. " << endl;
    }

    return 0;
}