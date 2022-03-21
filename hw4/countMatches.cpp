// CSCI1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 4 - Problem #4

// Problem: Write a program that asks for a string, a substring, and prints the number of times the substring is found in the string.

/* Algorithm:

Initialize variables for searchString, subString, and counter
Prompt and get input from the user for searchString and subString

For an integer i = 0, while i < searchString length, with i incrementing by 1,
    Initialize result variable
    result = the substring of searchString, starting at the i'th character, spanning the length of subString

    If result == subString
        Add one to counter

When the string is completely traversed, print the number of times the substring showed up (counter)

*/

#include <iostream>
#include <string>

using namespace std;

int main() {
    // Initialize variables
    string searchString;
    string subString;
    int counter = 0;

    // Prompt for and get input from user
    cout << "Enter the search string: " << endl;
    cin >> searchString;
    cout << "Enter the substring to be searched: " << endl;
    cin >> subString;
    
    // Traverse the string length, and search for if subString == the search result. If so, add it to a counter which will be printed
    for (int i = 0; i < searchString.length(); i++) {

        string result = searchString.substr(i, subString.length());

        if (result == subString) {
            counter++;
        }
    }

    // Print the number of times that the subString was found
    cout << "Number of occurrences: " << counter << endl;

    return 0;
}
