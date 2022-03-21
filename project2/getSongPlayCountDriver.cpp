// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project 2 - Problem #8

#include <iostream>
#include <fstream>
#include "Song.h"
#include "Listener.h"


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
toLower() - Takes in a string and returns the same string but all lowercase. Used for making countGenre case insensitive.
Parameters: str - The inputted string to be made lowercase
Returns: newStr - The output string which should be the same as string but in lowercase.
*/
string toLower(string str) {
    // Variable used to store new string. Initialize it to be the inputted string
    string newStr = str;

    // Traverse the inputted string
    for (int i = 0; i < str.length(); i++) {

        // If the character in the current string position is a capital letter (ascii), set the char in newStr to the lowercase equivalent
        if (str[i] >= 65 && str[i] <= 90) {
            newStr[i] = str[i] + 32;
        }
        // Else, if the character is not a capital letter, simply set the character in newStr to be the same character
        else {
            newStr[i] = str[i];
        }
    }

    // After the loop is completed, return the new string
    return newStr;
}

/*
getSongPlayCount() - Given a listener's name and a song name, returns the total number of plays of that song for that specific listener
Parameters:
    listenerName - The name of the listener (string)
    songName - The name of the song (string)
    listeners[] - The array of listener objects to be searched through (Listener)
    songs[] - The array of song objects to be searched through (Song)
    numberOfListeners - The number of listeners currently stored in listeners[] (int)
    numberOfSongs - The number of songs currently stored in songs[] (int)
Returns:
    The number of plays of the specific song for the specific listener
    If listener name is found but song name is not found, or if song file is empty, returns -1
    If song name is found but the listener name is not found, returns -2
    If both listener and song names are not found, returns -3
*/
int getSongPlayCount(string listenerName, string songName, Listener listeners[], Song songs[], int numberOfListeners, int numberOfSongs) {
    // Declare variables
    int listenerPlayCount = 0;  // Variable used to store the play count of the specified song by the specified listener
    int listenerIndex = -1;     // Stores the index of the specified listener. Initialized to -1 in the event that no matching listener is found
    int songIndex = -1;         // Stores the index of the specified song. Initialized to -1 in the evend that no matching song is found

    // Traverse listeners[].
    for (int i = 0; i < numberOfListeners; i++) {
        // If we find a match between the inputted listener name and the name of a listener in the array,
        if (toLower(listenerName) == toLower(listeners[i].getListenerName())) {
            // Store the index of this listener, and break from the traversal loop
            listenerIndex = i;
            break;
        }
    }

    // Traverse songs[]
    for (int i = 0; i < numberOfSongs; i++) {
        // If we find a match between the inputted song title and the title of a song in the array,
        if (toLower(songName) == toLower(songs[i].getTitle())) {
            // Store the index of this song, and break from the traversal loop
            songIndex = i;
            break;
        }
    }

    // These statements check if the song title and listener name were indeed found.
    // If both the listener and song could not be found in the array, return -3
    if (listenerIndex == -1 && songIndex == -1) {
        return -3;
    }
    // Else, if just the listener couldn't be found, return -2
    else if (listenerIndex == -1) {
        return -2;
    }
    // Else, if just the song couldn't be found, return -1
    else if (songIndex == -1) {
        return -1;
    }

    // If both the song title and listener name were found, we can proceed with finding the plays of that song for the listener
    // Set the listenerPlayCount equal to the number of plays of that particular song for that particular listener, then return that value.
    listenerPlayCount = listeners[listenerIndex].getPlayCountAt(songIndex);
    return listenerPlayCount;
}

// Main function for testing getSongPlayCount()
/* Expected Output:
3
5
-1
-2
-3
*/
int main() {
    // Setup
    Song songs[50];
    int numSongsStored = readSongs("songs2.txt", songs, 0, 50);
    cout << numSongsStored << endl;

    int numListenersStored = 0;
    int listenerArrSize = 50;
    Listener listener[listenerArrSize];
    numListenersStored = readListenerInfo("playlist.txt", listener, numListenersStored, listenerArrSize, 50);

    // Normal case test: both song name and listener name exist in the arrays
    numListenersStored = readListenerInfo("listenerInfo.txt", listener, numListenersStored, listenerArrSize, 50);
    cout<<getSongPlayCount("John", "Goodbye Yellow Brick Road", listener, songs, numListenersStored, numSongsStored)<<endl;

    // Edge case test: song name does not exist
    numListenersStored = readListenerInfo("listenerInfo.txt", listener, numListenersStored, listenerArrSize, 50);
    cout<<getSongPlayCount("John", "Master of Puppets", listener, songs, numListenersStored, numSongsStored)<<endl;

    // Edge case test: listener name does not exist
    numListenersStored = readListenerInfo("listenerInfo.txt", listener, numListenersStored, listenerArrSize, 50);
    cout<<getSongPlayCount("Gene", "Goodbye Yellow Brick Road", listener, songs, numListenersStored, numSongsStored)<<endl;

    // Edge case test: both listener and song name do not exist
    numListenersStored = readListenerInfo("listenerInfo.txt", listener, numListenersStored, listenerArrSize, 50);
    cout<<getSongPlayCount("Gene", "Master of Puppets", listener, songs, numListenersStored, numSongsStored)<<endl;

    return 0;
}