// CSCI1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project 1 - Problem #2

/* Problem: Write a function isConsonant that accepts a character as an argument and returns TRUE if the character passed into the function
is a Consonant, and FALSE otherwise. */

#include <iostream>

using namespace std;

/* isConsonant() - Checks an inputted character. Returns true if the char is a consonant, and returns false if it is not.
    Parameters: letter - Character to be checked (char)
    Returns: true or false - Depending on if letter is a consonant
*/
bool isConsonant(char letter) {
    const string consonants = "bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ";
    for (int i = 0; i < consonants.length(); i++) {

        if (letter == consonants[i]) {
            return true;
        }
    }
    return false;
}


// Main function for testing isConsonant(). Asks for a test letter input, and passes the input into isConsonant().
int main() {
    cout << "Test Letter" << endl;
    char input;
    cin >> input;
    cout << isConsonant(input) << endl;
    return 0;
}


