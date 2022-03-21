// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 8 - Problem #1

#include <iostream>
#include <vector>

using namespace std;

/* This program repeatedly asks the user to input numbers and adds certain values to a vector based on what the user inputs. It stops
when the user enters -1.
Algorithm/Pseudocode:
    Define a vector of values

    while userInput != -1
        print "Please enter a number: "
        get user input for userInput

        if userInput <= 0 && userInput != -1
            print "The number should be a positive integer or -1"

        else if the vector is empty
            add userInput to vector

        else
            if userInput % 5 == 0
                remove element from front of vector
            if userInput % 3 == 0
                remove element from end of vector (pop back)
            if userInput is not divisible by 5 or 3
                add the value of userInput to the vector


    Find minimum and maximum values in the vector
    if the vector is empty
        Print "The vector is empty."
    if the vector is not empty
        Print the contents of the vector
        Print the minimum value in the vector
        Print the maximum value in the vector
*/
int main() {
    // Declare variables
    vector<int> values;     // Defines the vector that will be manipulated throughout the course of the program
    int userInput = 0;      // Stores the value for the user input
    int minValue = 0;       // Stores the minimum value in the vector
    int maxValue = 0;       // Stores the maximum value in the vector

    while (userInput != -1) {
        // Prompt for and get input from the user
        cout << "Please enter a number:" << endl;
        cin >> userInput;

        // If the input was invalid, print a message reflecting this.
        if (userInput <= 0 && userInput != -1) {
            cout << "The number should be a positive integer or -1." << endl;
        }
        else if (values.size() == 0 && userInput != -1) {
            values.push_back(userInput);
        }
        // If the input was valid, check if it is divisible by 5 and 3
        else {
            // If the input is divisible by 5, remove the first element of the vector
            if (userInput % 5 == 0 && values.size() > 0) {
                values.erase(values.begin() + 0);
            }
            // If the input is divisible by 3, remove the last element of the vector
            if (userInput % 3 == 0 && values.size() > 0) {
                values.pop_back();
            }
            // If the input is neither divisible by 3 or 5, or vector is empty add the input to the end of the vector
            if (userInput % 5 != 0 && userInput % 3 != 0 && userInput != -1) {
                values.push_back(userInput);
            }
        }
    }

    // If the vector is empty, print a message reflecting this
    if (values.size() == 0) {
        cout << "The vector is empty." << endl;
    }
    // If the vector was not empty
    else {
        // Initialize max and min values to be the first value in the vector
        maxValue = values.at(0);
        minValue = values.at(0);
        // Loop through the vector and print out all the values. At the same time, search for the maximum and minimum values.
        cout << "The elements in the vector are: ";
        for (int i = 0; i < values.size(); i++) {

            cout << values.at(i) << " ";

            if (values.at(i) > maxValue) {
                maxValue = values.at(i);
            }
            if (values.at(i) < minValue) {
                minValue = values.at(i);
            }
        }
        // Start a new line, then print the min and max values of the vector
        cout << endl;
        cout << "Min = " << minValue << endl;
        cout << "Max = " << maxValue << endl;
    }
    return 0;
}