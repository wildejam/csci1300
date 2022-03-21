// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project 2 - Problem #11

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "Song.h"
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
countGenre() - Takes in an array of song objects and a genre, and returns the number of songs with that genre in the array. Not case sensitive.
Parameters:
    genre - the requested genre to be searched for (string)
    songs[] - The array of song objects to be searched through
    numSongsStored - The number of songs that are currently stored in songs[]
Returns:
    The number of songs in the array with the given genre
    Returns 0 if no songs match, songs[] is empty, or number of listeners is invalid
*/
int countGenre(string genre, Song songs[], int numSongsStored) {
    int counter = 0;        // Counter used to count number of songs with specified genre

    // Set genre equal to the lowercase version of the input. Essentially converts it to lowercase
    genre = toLower(genre);

    for (int i = 0; i < numSongsStored; i++) {
        // If lowercase genre of the song is equal to lowercase inputted genre, it's a match. Increment counter
        if (toLower(songs[i].getGenre()) == genre) {
            counter++;
        }
    }
    // After traversing the array, return the number of entries with the specified genre there were
    // Function will return 0 if array is empty or if no songs match
    return counter;
}

/*
frequentGenreSongs() - Finds most frequent genre from songs[] and returns the number of times that genre occurs
Parameters:
    songs[] - The array of songs to be searched (Song)
    numSongsStored - The number of songs stored in songs[] (int)
Returns:
    The number of songs of the most frequent genre
    If two genres have the same frequency, prints the number of songs of either one
    If no songs are found or songs[] is empty or number of songs stored is an invalid number, returns 0
*/
int frequentGenreSongs(Song songs[], int numSongsStored) {
    // Declare variables and arrays
    int genreCount = 0;                 // Stores the number of unique genres in songs[]
    int highestFrequency = 0;           // Variable used to store the largest frequency value in genreFrequency[]

    // If the playlist is not empty,
    if (numSongsStored > 0) {
        // Declare more variables. We do this after the if statement to avoid a segmentation fault, in case numSongsStored < 0
        string genres[numSongsStored];      // Array used to store the genres in songs[]
        int genreFrequency[numSongsStored]; // Array used to store genre frequencies in songs[].

        // Traverse songs[]
        for (int i = 0; i < numSongsStored; i++) {
            // Traverse genres[], and compare each element of genres[] to the current value of songs[].
            for (int j = 0; j < numSongsStored; j++) {
                // If at any point, the genre of the current song matches any of the genres already in genres[], it is not unique.
                if (toLower(songs[i].getGenre()) == toLower(genres[j])) {
                    // In which case, we should exit the genres[] traversal loop
                    break;
                }
                // If the loop gets to the end of the genres[] array and did not find a match, songs[i] must be a unique genre.
                else if (j = numSongsStored - 1) {
                    // So, add it to the array of genres
                    genres[genreCount] = songs[i].getGenre();
                    // Also, calculate the frequency that this genre appears in songs[] and populate genreFrequency[] with that frequency
                    genreFrequency[genreCount] = countGenre(songs[i].getGenre(), songs, numSongsStored);
                    // Then, increment genreCount
                    genreCount++;
                }
            }
        }

        // Now, once all of the unique genres and their frequencies have been recorded, we find the genre with the highest frequency
        // Start by initializing the highest frequency value to be the first frequency value in genreFrequency[]
        highestFrequency = genreFrequency[0];
        // Then traverse genreFrequency to find the position of the largest frequency value
        for (int k = 0; k < genreCount; k++) {
            // If the genreFrequency is larger that the current highest frequency, then that genre is the most frequent.
            if (genreFrequency[k] > highestFrequency) {
                highestFrequency = genreFrequency[k];
            }
        }

        return highestFrequency;
    }

    // If the playlist is empty, or the value of number of songs is stored is invalid, return 0
    else {
        return 0;
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

/*
addListener() - Adds a listener to the inputted listeners array. Will not add a listener if it has a duplicate name, case insensitive.
Parameters:
    listenerName - The name of the new listener that will be added. (string)
    listeners[] - The array of listeners to add the new listener to (Listener)
    numSongs - The number of songs (will be a constant value of 50) (int)
    numListenersStored - The number of listeners that are currently stored in listeners[] (int)
    listenersArrSize - The hard maximum capacity of listeners[]. Will be set to a constant value of 100.
Returns:
    If numListenersStored >= listenersArrSize, returns -1
    If a listener of the same name (case insensitive) already exists in listeners[], returns -2
    If listenerName is an empty string, returns -3
    Otherwise, this function will return the new number of listeners in the array, after adding the new one.
*/
int addListener(string listenerName, Listener listeners[], int numSongs, int numListenersStored, int listenersArrSize) {
    
    // Before anything, check for the edge cases
    // If the listeners array is full, do nothing and return -1
    if (numListenersStored >= listenersArrSize) {
        return -1;
    }
    // Traverse the listeners array. If there is a listener of the same name in listeners[], do nothing and return -2.
    for (int i = 0; i < numListenersStored; i++) {
        if (toLower(listenerName) == toLower(listeners[i].getListenerName())) {
            return -2;
        }
    }
    // If the listenerName input is an empty string, don't add it. Do nothing and return -3.
    if (listenerName == "") {
        return -3;
    }

    // Once all of those cases have been checked, the input must be valid and there must be space in the array.
    // So, set the name of the new listener to the name parameter and set all of the play counts of that listener to be 0.
    // Also, increment the number of listeners stored in listeners[]
    listeners[numListenersStored].setListenerName(listenerName);
    for (int i = 0; i < numSongs; i++) {
        listeners[numListenersStored].setPlayCountAt(i, 0);
    }
    numListenersStored++;

    // Then, return the number of listeners stored.
    return numListenersStored;
}

/*
getListenerStats() - Given a listener name and an array of listeners, prints the number of unique songs that listener listened to,
    as well as their average number of listens per song listened to. Returns 1, 0, or -3 depending on the input.
Parameters:
    listenerName - The name of the listener to find stats about (string)
    listeners[] - The array of listeners to be searched through (Listener)
    numListenersStored - The number of listeners stored in listeners[] (int)
    numSongs - The maximum number of songs stored in each listener object. Set to 50 in the final program. (int)
Returns:
    1 if the listener was found and the listener had listened to songs
    0 if the listener was found but the listener had no listens on any songs
    -3 if the listener was not found in listeners[]
*/
int getListenerStats(string listenerName, Listener listeners[], int numListenersStored, int numSongs) {
    // Declare variables
    int numUniqueSongs = 0;     // Stores the number of unique songs that the listener has listened to
    int listenSum = 0;          // Stores the sum of all of the listener's listens
    double listenAvg = 0;       // Stores the average number of listens for the listener

    // Start by traversing listeners[] and searching for the name of the listener
    for (int i = 0; i < numListenersStored; i++) {
        // If we find the listener in listeners[], proceed with processing the listener's info.
        if (toLower(listenerName) == toLower(listeners[i].getListenerName())) {

            // Traverse the listener's play counts. Add up the number of songs that have more than 1 listen, and add up the total listens
            for (int j = 0; j < numSongs; j++) {
                if (listeners[i].getPlayCountAt(j) > 0) {
                    numUniqueSongs++;
                    listenSum += listeners[i].getPlayCountAt(j);
                }
            }

            // After reading the listener's playCount info, if the listener had not listened to any songs, print a message and return 0.
            if (numUniqueSongs == 0 && listenSum == 0) {
                cout << listenerName << " has not listened to any songs. " << endl;
                return 0;
            }

            // Else if the listener had song listens, calculate the average number of listens. Multiply by 1.0 to get the average as a double.
            listenAvg = (listenSum * 1.0) / (numUniqueSongs * 1.0);

            // Print the listener's unique songs listened to, and the average number of listens to 2 decimal precision.
            cout << listenerName << " listened to " << numUniqueSongs << " songs. " << endl;
            cout << fixed << setprecision(2) << listenerName << "'s average number of listens was " << listenAvg << endl;
            // Then return 1.
            return 1;
        }
    }

    // If the program reaches this point, it means that no matching listener was found in listeners[].
    // So, print a message reflecting this, and return -3.
    cout << listenerName << " does not exist. " << endl;
    return -3;
}


/*
This program presents the user with a menu that runs on a loop of the following options. It also creates a database of listeners
and songs that the user may interact with. The program supports a max of 50 songs and 100 listeners.

1. Read songs from file
    Reads a file of songs with song info and inputs the songs into the database as song objects
2. Print all songs
    Prints out all of the songs currently stored into the database
3. Song-count by genre
    Counts the number of songs in the database of a specified genre
4. Songs from most common genre
    Counts the number of songs in the database of the most frequently appearing genre in the database
5. Add listener
    Adds a listener to the listener database
6. Read listens from file
    Reads listener info from a file and stores it in the listener database
7. Get song listens by a listener
    Prints the play count of a specific song for a specific listener
8. Get listener statistics
    Gets the stats of a listener according to getListenerStats()
9. Quit
    Prints a goodbye message and exits the program

Depending on what the user chose to do, a certain function is run. If the user chooses an invalid option, prints "Invalid input."
*/
int main() {
    // Declare variables and arrays
    int userInput;                      // Stores the user input for navigating menus  
    string userStrInput;                // Used to store input from the user in cin statements
    string userStrInput2;               // Used to store input form the user in cin statements
    int maxSongs = 50;                  // Stores the max number of songs the program can support, being 50 songs
    int maxListeners = 100;             // Stores the max number of listeners the program can support, being 100 listeners
    int numSongs = 0;                   // Stores the number of songs currently stored in songs[]
    int numListeners = 0;               // Stores the number of listeners currently stored in listeners[]
    int functionReturn = 0;             // Stores the return values of functions when they are called
    Song songs[maxSongs];               // Array used to store songs
    Listener listeners[maxListeners];   // Array used to store listeners

    // While the user does not wish to quit the program,
    while (userInput != 9) {

        // Print the menu of options
        cout << "Select a numerical option:\n"
        "======Main Menu=====\n"
        "1. Read songs from file\n"
        "2. Print all songs\n"
        "3. Song-count by genre\n"
        "4. Songs from most common genre\n"
        "5. Add listener\n"
        "6. Read listens from file\n"
        "7. Get number of listens by a listener\n"
        "8. Get listener statistics\n"
        "9. Quit" << endl;

        // And get input from the user about what they wish to do
        cin >> userInput;

        // If the user wishes to read songs from a file,
        if (userInput == 1) {

            // Prompt for and get input for a file name to be read
            cout << "Enter a song file name: " << endl;
            cin >> userStrInput;

            // Pass the user input into the readSongs() function
            functionReturn = readSongs(userStrInput, songs, numSongs, maxSongs);

            // If the function did not return -1 or -2, update the new number of songs in songs[], and print the amount of songs in songs[].
            if (functionReturn != -1 && functionReturn != -2) {
                numSongs = functionReturn;
                cout << "Total songs in the database: " << numSongs << endl;
                // If the function returned the max number of songs, songs may not have been added. Print a message reflecting this.
                if (functionReturn == maxSongs) {
                    cout << "Database is full. Some songs may have not been added. " << endl;
                }
            }
            // If the function returned -1, print "No songs saved to the database."
            else if (functionReturn == -1) {
                cout << "No songs saved to the database. " << endl;
            }
            // If the function returned -2, print "Database is already full. No songs were added."
            else if (functionReturn == -2) {
                cout << "Database is already full. No songs were added. " << endl;
            }

        }

        // If the user wishes to print all songs in the database, print them using printAllSongs()
        else if (userInput == 2) {
            printAllSongs(songs, numSongs);
        }

        // If the user wishes to count songs by genre,
        else if (userInput == 3) {
            // Prompt for and get input for the genre to be searched
            cout << "Genre: " << endl;
            cin >> userStrInput;
            // Then print the total number of songs in the database of that genre
            cout << "Total " << userStrInput << " songs in the database: " << countGenre(userStrInput, songs, numSongs) << endl;
        }

        // If the user wishes to count songs of the most common genre,
        else if (userInput == 4) { 
            // Print the total number of songs of the most common genre
            cout << "Number of songs in most common Genre: " << frequentGenreSongs(songs, numSongs) << endl;
        }

        // If the user wishes to add a listener,
        else if (userInput == 5) {
            // Flush userStrInput, so that getline() will function properly
            getline(cin, userStrInput);
            // Prompt for and recieve a listener name
            cout << "Enter a listener name: " << endl;
            getline(cin, userStrInput);

            // Pass the input into the addListener() function
            functionReturn = addListener(userStrInput, listeners, maxSongs, numListeners, maxListeners);

            // If the listeners array is full (function returns -1), print a message reflecting this
            if (functionReturn == -1) {
                cout << "Database is already full. Listener cannot be added. " << endl;
            }
            // If the listener name already exists (function returns -2), print a message reflecting this
            else if (functionReturn == -2) {
                cout << "Listener already exists." << endl;
            }
            // If the listener name input is an empty string (function returns -3), print a message reflecting this
            else if (functionReturn == -3) {
                cout << "The listenerName is empty. " << endl;
            }
            // If the listener was added successfully, print a message reflecting this and increment the listeners
            else {
                cout << "Welcome, " << userStrInput << "! " << endl;
                numListeners++;
            }
        }

        // If the user wishes to read listeners from a file,
        else if (userInput == 6) {
            // Prompt for and get input for a file name to read listeners from
            cout << "Enter the listener info file name: " << endl;
            cin >> userStrInput;

            // Pass the input into the readListenerInfo() function. maxCol = maxSongs + 1, as there is one extra column for the name
            functionReturn = readListenerInfo(userStrInput, listeners, numListeners, maxListeners, maxSongs + 1);

            // If the function did not return either -1 or -2,
            if (functionReturn != -1 && functionReturn != -2) {
                // Set the new number of listeners and print a message displaying this.
                numListeners = functionReturn;
                cout << "Total listeners in the database: " << numListeners << endl;
                // If the number of listeners equals the maximum number of listeners, print a message saying some may not have been added
                if (numListeners == maxListeners) {
                    cout << "Database is full. Some listeners may have not been added. " << endl;
                }
            }
            // If the function returned -1, print the following message
            else if (functionReturn == -1) {
                cout << "Nothing saved to the database. " << endl;
            }
            // If the function returned -2, print the following message
            else if (functionReturn == -1) {
                cout << "Database is already full. Nothing was added. " << endl;
            }
        }

        // If the user wishes to get the number of listens by a listener,
        else if (userInput == 7) {
            // Flush userStrInput, so that getline() will function properly
            getline(cin, userStrInput);
            // Prompt and get input for a listener name and a song name
            cout << "Enter a listener name: " << endl;
            getline(cin, userStrInput);
            cout << "Enter a song name: " << endl;
            getline(cin, userStrInput2);

            // Pass the inputs into the getSongPlayCount() function
            functionReturn = getSongPlayCount(userStrInput, userStrInput2, listeners, songs, numListeners, numSongs);

            // If both the listener and song don't exist, print a message reflecting this
            if (functionReturn == -3) {
                cout << userStrInput << " and " << userStrInput2 << " do not exist. " << endl;
            }
            // Else if the song name does not exist, print a message reflecting this
            else if (functionReturn == -1) {
                cout << userStrInput2 << " does not exist. " << endl;
            }
            // Else if the listener name doesn't exist, print a message reflecting this
            else if (functionReturn == -2) {
                cout << userStrInput << " does not exist. " << endl;
            }
            // If the listener name and song name exist, print the results of the function
            else {
                cout << userStrInput << " has listened to " << userStrInput2 << " " << functionReturn << " times. " << endl;
            }
        }

        // If the user wishes to get a listener's statistics,
        else if (userInput == 8) {
            // Prompt and get input for a listener name, then pass it into getListenerStats()
            cout << "Enter a listener name: " << endl;
            cin >> userStrInput;
            getListenerStats(userStrInput, listeners, numListeners, maxSongs);
        }

        // If the user wishes to quit the program, print a goodbye message.
        else if (userInput == 9) {
            cout << "Good bye! " << endl;
        }

        // If the user's input is invalid, print "Invalid input."
        else {
            cout << "Invalid input. " << endl;
        }
    }
    return 0;
}