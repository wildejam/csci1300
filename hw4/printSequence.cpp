// CSCI1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 4 - Problem #2

// Problem: Take an input for a value, and repeatedly put it through the mathematical sequence as shown in the problem until it reaches 1

/* Algorithm:

Initialize long int variable for n
Prompt user for and get input for value of n

While n > 1
    If n is even, NOT 0, and positive,
        Print n
        n = sqrt(n)
    Else if n is odd, NOT 0, and positive,
        Print n
        n = sqrt(n)^3
    Else
        Print "Invalid input."

*/

#include <iostream>
#include <cmath>

using namespace std;

int main() {
    // Initialize n
    long int n = 0;


    // Prompt user for and recieve input for n
    cout << "Enter a positive integer: " << endl;
    cin >> n;

    // If the input is negative, print Invalid Input
    if (n <= 0) {
        cout << "Invalid input. " << endl;
    }

    // If input is valid, print n, then process the input
    else if (n > 0) {

        cout << n << endl;

        // Until n = 1, if n is even, take the square root of n then print it. If n is odd, take square root then cube it and print.
        while (n > 1) {

            if (n % 2 == 0 && n > 0) {
                n  = sqrt(n);
                cout << n << endl;

            }

            else if (n % 2 == 1 && n > 0) {
                n = pow(sqrt(n),3);
                cout << n << endl;
            }
        }
    }

    return 0;
}