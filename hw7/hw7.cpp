// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 7 - Problem #6

#include <iostream>
#include <string>
#include <fstream>
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


/*
printAllSongs() - Takes an array of song objects and prints all of the songs to the console.
Parameters:
    songs[] - The array of song objects from which to print the data (Song)
    numsongs - The number of songs currently stored in songs[] (int)
Returns: Nothing
*/
void printAllSongs(Song songs[], int numsongs) {

    // If there are songs in the array,
    if (numsongs > 0) {
        // Print an introductory message,
        cout << "Here is a list of songs " << endl;
        // Then print the name and artist of each song in the array in the format specified by the problem
        for (int i = 0; i < numsongs; i++) {
            cout << songs[i].getTitle() << " is by " << songs[i].getArtist() << endl;
        }
    }

    // If there are no songs in the array, print "No songs are stored".
    else {
        cout << "No songs are stored" << endl;
    }

}


/*
This program gives the user a menu that runs on a loop until the user decides to quit. The menu has 3 options: Read songs, Print Songs, and Quit.
Depending on the option the user chooses, a certain function will be run.
    Read Songs lets the user input a file name to be read, and the songs from the file will be added to the system.
    Print Songs prints all of the songs in the system for the user to see, as well as their artists
    Quit terminates the program with a goodbye message.
The capacity of the system is 50 songs.
If the user inputs a choice into the menu that is not valid, the program prints invalid input and displays the menu once more.
*/
int main() {
    // Declare variables
    Song songs[50];     // Stores the songs. A maximum of 50 songs is permitted for this program
    int storedSongs = 0;// Stores the number of songs currently stored in the system. Cannot exceed 50.
    int choice = 0;     // Stores the choice that the user inputted for navigating the menu
    string fileName;    // Stores the file name of a file the user wants to read for songs

    // While the user does not wish to quit the program,
    while (choice != 3) {
        // Print the menu
        cout << "======Main Menu=====\n"
                "1. Read songs\n"
                "2. Print all songs\n"
                "3. Quit" << endl;
        // And take user input for their desired choice
        cin >> choice;

        // If the user chooses to read songs, proceed with the process for reading and adding songs to the system.
        if (choice == 1) {
            // Prompt and get input for file name to read songs from
            cout << "Enter a song file name: " << endl;
            cin >> fileName;


            // If the function returned a -2, the database is full. Print a message reflecting this.
            if (readSongs(fileName, songs, storedSongs, 50) == -2) {
                cout << "Database is already full. No songs were added." << endl;
            }

            // If the function returned a -1, the file was not opened successfully. Print an error message.
            else if (readSongs(fileName, songs, storedSongs, 50) == -1) {
                cout << "No songs saved to the database." << endl;
            }

            // If the number of songs now equals 50, database is full, and songs may have been skipped. Print a message reflecting this.
            else if (readSongs(fileName, songs, storedSongs, 50) == 50) {
                cout << "Database is full. Some songs may not have been added." << endl;
            }
            // Else, if the function passed, print the total number of songs in the database.
            else {
                storedSongs = readSongs(fileName, songs, storedSongs, 50);         // Update storedSongs with new song count
                cout << "Total songs in the database: " << storedSongs << endl;     // Print the new number of songs in database
            }

        }

        // If the user chooses to print all songs, proceed with printing all songs in the system
        else if (choice == 2) {
            printAllSongs(songs, storedSongs);
        }

        // If the user chooses to quit, print a goodbye message. Loop will be exited and program will terminate
        else if (choice == 3) {
            cout << "Good bye! " << endl;
        }

        // If the users input was none of the available options, print "Invalid input."
        else {
            cout << "Invalid input. " << endl;
        }
        
    }
    return 0;
}