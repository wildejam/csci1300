// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 6 - Problem #2

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;
/*
split(): Takes in a string and a delimiter character, splits the string into sections separated by the delimiter character, and
    populates an array with the split pieces of the string. Returns the number of pieces the string was split into. Returns
    -1 if the number of split pieces is larger than the size of the array.
Parameters:
    str - The string to be split (string)
    delimiter - The designated delimiter character (char)
    arr[] - The array where the split pieces of the string will be stored (string)
    arraySize - The size of the pieces[] array (int)
Returns: pieceCounter - The number of pieces that the string was split into (int)
*/
int split(string str, char delimiter, string arr[], int arraySize) {
    // Initialize variables for number of pieces, current position of arr[], stringLength, and temporary variable to hold a piece of a string
    int pieceCounter = 0;
    int arrayPos = 0;
    int stringLength = str.length();
    string piece;

    // Traverse the string, one character at a time
    for (int i = 0; i < stringLength; i++) {

        // If the traversal lands on the delimiter character OR the end of the string is reached...
        if (str[i] == delimiter || i == stringLength - 1) {

            // ...if this if statement was triggered by the end of the string being reached, add the final character to piece...
            if (i == stringLength - 1) {
                piece = piece + str[i];
            }

            // ... and add the current string as an array element to arr[], and reset piece to be empty. 
            // Also add 1 to the number of pieces in arr[].
            arr[arrayPos] = piece;
            arrayPos++;
            piece = "";
            pieceCounter++;


        }
        // Else, if the current string character is not equal to the delimiter, add the character to piece
        else {
            piece = piece + str[i];
        }
    }

    // If the inputted string was empty, exit the function and return 0.
    if (str == "") {
        return 0;
    }

    // If the number of pieces fits into the alotted size of the array, return pieceCounter
    if (pieceCounter <= arraySize) {
        return pieceCounter;
    }
    // Else if the number of pieces exceeds the allotted array size, return -1
    else {
        return -1;
    }
}

/* 
workHours() - Reads an inputted text file, stores the name and monthly work hours in arrays, prints avg monthly hours for each employee, and
              Returns the number of employees stored. If file cannot be opened, returns -1.
Parameters:
    fileName - The user-inputted name of the file to link to (string)
    names[] - The array to store the names of the employees in (string)
    hours[] - A 2D array that stores the monthly hours. 12 columns. Each row corresponds to a specific employee (int)
    namesSize - The size of the store names array (int)
Returns: employeeCount - Number of employees stored in the string array
*/
int workHours(string fileName, string names[], int hours[][12], int namesSize) {
    // Declare variables.
    ifstream hoursDocument;     // ifstream object for reading the file
    string line;                // stores the current line being read
    string strHours[12];        // stores the string versions of the monthly hours, to eventually be converted to int
    int employeeCount = 0;      // variable used to store the number of employees
    double sum = 0;             // stores the sum of an employee's monthly hours. used to calculate avgHours
    double avgHours = 0;        // stores the average monthly work-hours for a particular employee
    
    // Open the document with the given filename
    hoursDocument.open(fileName);

    // If the document is open
    if (hoursDocument.is_open()) {

        // Read the document until there are no more lines left
        while(getline(hoursDocument, line)) {

            // If the employeeCount is not greater than the size of the array
            if (employeeCount < namesSize) {
                
                names[employeeCount] = line;        // Fill names[] with the current line (which should be the name)

                getline(hoursDocument, line);       // Get the next line, which should be the hours for the preceding employee
                split(line, ',', strHours, 12);     // Split the line, and populate strHours with the string versions of those hours

                // Fill each column of hours[] with the integer versions of the hours for the corresponding employee
                for (int j = 0; j < 12; j++) {
                    hours[employeeCount][j] = stoi(strHours[j]);
                }

                // Calculate the average of all of the hours for the current employee
                for (int k = 0; k < 12; k++) {
                    sum += hours[employeeCount][k];
                }
                avgHours = sum / 12;

                // Print the name and average monthly hours of the current employee to the console, to 1 decimal precision
                cout << fixed << setprecision(1) << names[employeeCount] << ": " << avgHours << endl;

                // Increment employeeCount, and reset sum for the next employee
                employeeCount++;
                sum = 0;
            }
        }
        // Return the number of employees that were processed
        return employeeCount;
    }

    // Return -1 if the document could not be opened
    else {
        return -1;
    }
}

// main function for testing workHours()
int main() {
    string fileName;
    string names[3];
    int hours[3][12];
    int namesSize = 3;

    cout << "Enter filename: " << endl;
    cin >> fileName;
    cout << workHours(fileName, names, hours, namesSize) << endl;

    return 0;
}