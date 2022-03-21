// CSCI1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 4 - Extra Credit Problem

/* Problem: Write a program that takes the side length of the diamond, then it prints the inverse of the diamond like below.
Make sure your program validates the user input. If the user tries to input a negative number,print ”Invalid input.”

*/

/* Algorithm:

Initialize variables:
    length integer - this will be used to store user input
    lineLength integer - this will keep track of the length of the line
    height integer - this will keep track of the height of the figure
Prompt for and get input from user for length

If input is valid (is not negative):
    For height from 0 to 2 * length - 1, with height incrementing by 1
        For lineLength from 0 to (2 * length) + 1, with lineLength incrementing by 1
            If lineLength <= length - height || lineLength > ((2 * length) + 1) - (2 * height + 1)
                Print "*"
            Else
                Print " "

Else if input is not valid:
    Print "Invalid input."

*/

#include <iostream>

using namespace std;

int main() {
    // Initialize variables
    int length = 0;
    int lineLength = 0;
    int height = 0;

    // Prompt for and get input from user
    cout << "Enter the length: " << endl;
    cin >> length;

    // If input is valid:
    if (length > 0) {

        // For height from 0 to the input value:
        for (height = height; height < 2 * length - 1; height++) {

            // For the length of the line from 0 to (the input length * 2 + 1):
            for (lineLength = lineLength; lineLength < 2 * length + 1; lineLength++) {

                // If either the line length is less than the length minus height, OR is greater than the length of the whole line minus the length
                // of the spaces:
                if (lineLength <= (length - height) || lineLength > (2 * length + 1) - (length - height + 1)) {

                    // Print a *
                    cout << "*";

                }

                // Else, lineLength must be in a place where there should be a space
                else {

                    // So, print a space
                    cout << " ";

                }
            }

            // When the length of the line reaches the end point, start a new line and set lineLength = 0
            cout << endl;
            lineLength = 0;

        }
    }

    // Else, if the input is invalid, print "Invalid input."
    else {
        cout << "Invalid input. " << endl;
    }

    return 0;
}

// THIS CODE IS INCOMPLETE. THE ALGORITHM USED IS SLIGHTLY WRONG, AND THIS IS AN EXTRA CREDIT QUESTION THAT I NO LONGER HAVE TIME FOR.