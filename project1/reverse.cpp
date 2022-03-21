// CSCI1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project 1 - Problem #1

// Problem: Write a function named reverse()that takes a number (as a string) as a function parameter and prints that number in reverse.

// reverse() - Takes a string as an input, and prints it in reverse
// @param number - number to be reversed (string)
// @return none

#include <iostream>
using namespace std;


// This reverse() function takes a string as an input, and prints the reverse order of the string
// Parameters: number - the string to be input
// Returns: nothing
void reverse(string number) {

    // Print every value in "number", starting from the last string element and moving to the first
    for (int i = number.length() - 1; i >= 0; i-- ) {
        cout << number[i];
    }
    cout << endl;
}

int main() {
    string input = "";
    cout << "input: " << endl;
    cin >> input;

    reverse(input);
    
    return 0;
}

