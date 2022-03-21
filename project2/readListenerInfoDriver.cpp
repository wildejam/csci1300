// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project 2 - Problem #7

#include <iostream>
#include <fstream>
#include "Listener.h"

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
readListenerInfo() - Reads a playlist file, populates an array listeners[] with information from that file, and returns the number of listeners.
Parameters:
    filename - The inputted name of the file to be read for information (string)
    listeners[] - The inputted array that will be filled with listeners from filename. Can be partially filled. (Listener array)
    numListenersStored - the number of listeners currently stored in listeners[]. (int)
    listenerArrSize - The hard capacity of listeners[]. Default will be 100.
    maxCol - The maximum number of columns. Default value will be 51.
Returns:
    The number of listeners stored in listeners[] after listeners are added from reading the file.
    If numListenersStored >= listenerArrSize, returns -2
    If filename is a file that cannot be opened, returns -1
    If the file was opened but was empty upon reading, returns 0
*/
int readListenerInfo(string filename, Listener listeners[], int numListenersStored, int listenerArrSize, int maxCol) {
    // Declare variables
    string line;
    string listenerInfo[maxCol];
    int initialNumListenersStored = numListenersStored;
    int listenerInfoEntryCount = 0;
    ifstream listenersDocument;

    // If the number of listeners stored in listeners[] is greater than or equal to the size of listeners[], exit and return -2
    if (numListenersStored >= listenerArrSize) {
        return -2;
    }

    // Open the file. If the file could not be opened, return -1
    listenersDocument.open(filename);
    if (listenersDocument.fail()) {
        return -1;
    }

    // If the document didn't fail, it must have opened successfully. Read the document until either there are no more lines to read,
    // or the number of listeners stored in listeners[] reaches the listener array size
    while (getline(listenersDocument, line) && numListenersStored < listenerArrSize) {
        // If the line being read is not empty,
        if (line != "") {
            // Split the line into each individual component, populating listenerInfo with that information, and store the number of pieces
            listenerInfoEntryCount = split(line, ',', listenerInfo, maxCol);

            // Set the listener name at the position indicated by the number of stored listeners there are to the name that was just read
            listeners[numListenersStored].setListenerName(listenerInfo[0]);

            // Then, we need to populate the playCount array of that specific listener object. Traverse the playCount array.
            // (Segmentation faults should never occur as listenerInfoEntryCount should never be higher than 51.)
            for (int i = 0; i < listenerInfoEntryCount - 1; i++) {
                // And set the play counts to be the play counts that were just read. i + 1 accounts for the first element being the name.
                listeners[numListenersStored].setPlayCountAt(i, stoi(listenerInfo[i + 1])); 
            }

            // At this point, the listener name and their playCount have been successfully stored. Increment the number of listeners.
            numListenersStored++;
        }
    }

    // Once the document has been processed, check to see if the file was empty. Return 0 if it was.
    if (numListenersStored == initialNumListenersStored) {
        return 0;
    }

    // If the document was not empty, and the listener count was increased, return the new total number of listeners stored in the array.
    else {
        return numListenersStored;
    }
}

// Main function for testing readListenerInfo()
/* Expected Output:
50
-2
-1
0
*/
int main() {
    // Standard test
    string fileName1 = "listeners.txt";
    int listenerArrSize1 = 100;
    Listener listeners1[listenerArrSize1];
    int numListenersStored1 = 0;
    int maxCols1 = 51;
    cout << readListenerInfo(fileName1, listeners1, numListenersStored1, listenerArrSize1, maxCols1) << endl;

    // numListenersStored equals listenerArrSize
    int numListenersStored2 = 100;
    cout << readListenerInfo(fileName1, listeners1, numListenersStored2, listenerArrSize1, maxCols1) << endl;


    // file does not exsit
    string fileName2 = "lol.txt";
    cout << readListenerInfo(fileName2, listeners1, numListenersStored1, listenerArrSize1, maxCols1) << endl;

    // empty file
    string fileName3 = "empty.txt";
    cout << readListenerInfo(fileName3, listeners1, numListenersStored1, listenerArrSize1, maxCols1) << endl;

    return 0;
}