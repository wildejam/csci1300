// CSCI1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project 1 - Problem #2

/*
Problem: Write a function named numConsonant(). 
The function should accept one parameter of type string and it should return how many consonants are in the string. 
You should use the helper function isConsonant(), developed in the previous question.
*/

#include <iostream>

using namespace std;


// This function checks a character that it takes as a parameter. If the character is a consonant, it returns true. If not, it returns false.
bool isConsonant(char letter) {
    const string consonants = "bcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ";
    for (int i = 0; i < consonants.length(); i++) {

        if (letter == consonants[i]) {
            return true;
        }
    }
    return false;
}

/*
numConsonant() - Takes a string and returns how many consonants are in the string
Parameters: str - string to be checked (string)
Returns: Number of consonants in the string (int)
*/
int numConsonant(string str) {
    int counter = 0;

    for (int i = 0; i < str.length(); i++) {

        if (isConsonant(str[i])) {
            counter++;
        }
    }
    return counter;
}

// Main function for testing. Asks for a string as input, plugs it into numConsonant(), and prints number of consonants to the console
int main() {
    string input = "";

    cout << "Test string: " << endl;
    cin >> input;
    cout << numConsonant(input) << endl;

    return 0;
}