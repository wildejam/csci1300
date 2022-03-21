// CSCI1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 4 - Problem #5

// Problem: Write a program that takes the height of the triangle (integer > 0), and prints an alphabetical triangle

/* Algorithm:

Initialize variables and constant:
    integer height - this will be used to take input for height of the pyramid
    integer length - this will be used to compute the length of the current line
    integer characterPosition - this will be used to keep track of the character the program is on
    constant string alphabet = "abcdefghijklmnopqrstuvwxyz"
    
Prompt user for and get input for height

Input validation; If the input is >= 0,

    While the height >= 1, with the height decrementing upon each iteration,

        While the length is less than the height, decrementing upon each iteration,

            Print the substring of alphabet according to the characterPosition (should print a single character)
            Increment characterPosition by 1

            If characterPosition >= 26 (meaning that it passes the letter z),
                Reset characterPosition to 0

        When the length reaches the height, start a new line and reset length to 0
        
Else, if the input is invalid,
    Print "Invalid input."
    
*/

#include <iostream>
#include <string>

using namespace std;

int main() {
    // Initialize variables & constant
    int height = 0;
    int length = 0;
    int characterPosition = 0;
    const string alphabet = "abcdefghijklmnopqrstuvwxyz";
    

    // Prompt for and get input from the user
    cout << "Enter the height: " << endl;
    cin >> height;

    // If input is valid (positive):
    if (height >= 0) {

        // While the height is greater than 1, with the height decrementing by 1 for each line:
        for (height = height; height >= 1; height--) {
            
            // While the length of the line is less than the current height, with the length incrementing by 1 each character:
            for (length = 0; length < height; length++){

                // Print the substring of the alphabet indicated by the current character, and move the characterPosition up by 1
                cout << alphabet.substr(characterPosition, 1);
                characterPosition++;

                // If at any point the character position is out of bounds of the alphabet string (at z), reset it to the beginning (to a)
                if (characterPosition >= 26) {
                        characterPosition = 0;
                }
            }

            // When the length reaches 0, Start a new line, and reset the length to 0
            cout << endl;
            length = 0;
        }
    }

    // If the input is invalid, print "Invalid input."
    else {
        cout << "Invalid input." << endl;
    }

    return 0;
}