// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 7 - Problem #4
#include <iostream>
#include <fstream>
#include <string>
#include "Song.h"

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
readSongs() -   Reads a file with song information, and fills an array of song objects with that information.
                Returns total number of songs in the array.
Parameters:
    fileName - The name of the file to be read for song information (string)
    songs[] - The inputted array of Song objects (Song)
    numSongsStored - number of songs currently stored in the array (int)
    songArrSize - Capacity of the song array
Returns: 
    numSongsStored - Total number of songs stored in the system
    -2 if numSongsStored == songArrSize
    -1 if file is not opened successfully
*/
int readSongs(string fileName, Song songs[], int numSongsStored, int songArrSize) {
    // Declare variables
    ifstream songFile;      // Stream that is linked to the file that the user desires to open
    string line;            // Line used to store the line currently being read from the file
    string songSplit[3];    // Array used to store the string values of the line currently being read. Used in split().

    // Before anything, start by checking if the songs number is equal to the array size. If so, return -2.
    if (numSongsStored == songArrSize) {
        return -2;
    }

    // Open the file with the song data
    songFile.open(fileName);

    // If the song file was opened successfully, process the information
    if (songFile.is_open()) {
        // While the number of stored songs does not exceed the size of the array, and there are lines in the file to be read,
        while (numSongsStored < songArrSize && getline(songFile, line)) {

            // If the line is not empty
            if (line != "") {

                // Split the current line into 3 parts (name, artist, genre), and fill songSplit with those parts
                split(line, ',', songSplit, 3);

                // Populate songs[] with a new Song object parameterized by the data read from the file
                songs[numSongsStored] = Song(songSplit[0], songSplit[1], songSplit[2]);

                // Increment the number of songs that are stored in the array
                numSongsStored++;
            }
        }
        // Once the data has been sufficiently processed, return the number of songs that are stored in the array
        return numSongsStored;
    }
    // If the song file was NOT opened successfully, return -1.
    else {
        return -1;
    }
}


// Main function used for testing readSongs()
/* Expected Output:
50
Love Me Do
From Me to You
The Beatles
The Beatles
Rock
Rock
-2
Cotton Tail
Hikaru Nara
Duke Ellington
Goose House
Jazz
J-Pop
*/
int main() {
    // General Test
    string fileName = "songs.txt";
    Song songs[50];
    int numberOfSongsStored = 0;
    int arraySize = 50;

    cout << readSongs(fileName, songs, numberOfSongsStored, arraySize) << endl;
    cout << songs[0].getTitle() << endl;
    cout << songs[1].getTitle() << endl;
    cout << songs[0].getArtist() << endl;
    cout << songs[1].getArtist() << endl;
    cout << songs[0].getGenre() << endl;
    cout << songs[1].getGenre() << endl;

    // Songs array already full test
    string fileName2 = "songs.txt";
    Song songs2[2];
    songs2[0].setTitle("Cotton Tail");
    songs2[0].setArtist("Duke Ellington");
    songs2[0].setGenre("Jazz");
    songs2[1].setTitle("Hikaru Nara");
    songs2[1].setArtist("Goose House");
    songs2[1].setGenre("J-Pop");
    int numberOfSongsStored2 = 2;
    int arraySize2 = 2;

    cout << readSongs(fileName2, songs2, numberOfSongsStored2, arraySize2) << endl;
    cout << songs2[0].getTitle() << endl;
    cout << songs2[1].getTitle() << endl;
    cout << songs2[0].getArtist() << endl;
    cout << songs2[1].getArtist() << endl;
    cout << songs2[0].getGenre() << endl;
    cout << songs2[1].getGenre() << endl;

    return 0;
}