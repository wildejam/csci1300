// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 6 - Problem #1

#include <iostream>
#include <fstream>

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
using namespace std;
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


int main() {
    // Start by defining variables and an input filestream object
    ifstream inventory;         // Opens the input stream
    string fileName;            // Stores user input for the fileName to connect to
    int lineCount = 0;          // Stores the number of lines in the file
    double highestPrice = 0;    // Stores the highest price in the file
    double lowestPrice = 0;     // Stores the lowest price in the file
    string mostExpensive;       // Stores the most expensive item in the file
    string leastExpensive;      // Stores the least expensive item in the file
    string linePieces[2];       // Array used for splitting lines with the split() function
    int linePiecesSize = 2;     // Size of linePieces[] for the split() function


    // Prompt user for filename and link it to the inventory object
    cout << "Enter the file name: " << endl;
    cin >> fileName;
    inventory.open(fileName);

    // If the file was successfully opened, proceed with the processing
    if (inventory.is_open()) {
        // Define a variable called line that will store the current line of the file
        string line;
        // While there are lines to be read in the file,
        while (getline(inventory, line)) {
            // If the line is not empty,
            if (line != "") {

                // Populate the array of "linePieces" with the store item and price of the current line by splitting the string
                split(line, ',', linePieces, linePiecesSize);

                // If the line currently being read is the first proper entry, initialize the highest and lowest prices to be the first entry
                if (lineCount == 0) {
                    highestPrice = stod(linePieces[1]);
                    lowestPrice = stod(linePieces[1]);
                    mostExpensive = linePieces[0];
                    leastExpensive = linePieces[0];
                }

                // If the price of the item is larger than the current largest price, set largest priced item equal to that item
                if (stod(linePieces[1]) > highestPrice) {
                    highestPrice = stod(linePieces[1]);
                    mostExpensive = linePieces[0];
                }

                // If the price of the item is smaller than the current smallest price, set smallest priced item equal to that item
                if (stod(linePieces[1]) < lowestPrice) {
                    lowestPrice = stod(linePieces[1]);
                    leastExpensive = linePieces[0];
                }

                // Add one to the lineCount for every line that is processed
                lineCount++;
            }
        }

        // After the file is done being read, print the results to the console
        cout << "The number of lines: " << lineCount << endl;
        cout << "The most expensive product: " << mostExpensive << endl;
        cout << "The least expensive product: " << leastExpensive << endl;
    }

    // If the file could not be opened, print an error message
    else {
        cout << "Could not open file. " << endl;
    }

    return 0;
}   