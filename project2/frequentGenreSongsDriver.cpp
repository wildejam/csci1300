// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project 2 - Problem #5

#include <iostream>
#include <string>
#include "Song.h"

using namespace std;

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

// Main function used for testing frequentGenreSongs()
/* Expected Output:
3

1

0
*/
int main() {

    // Normal test case
    Song song1("", "", "pop");
    Song song2("", "", "pop");
    Song song3("", "", "jazz");
    Song song4("", "", "edm");
    Song song5("", "", "pop");
    Song testArray1[5] = {song1, song2, song3, song4, song5};
    int numSongs = 5;

    cout << frequentGenreSongs(testArray1, numSongs) << endl;
    cout << endl;

    // All genres have same frequency test case. Also tests case sensitivity
    Song song6("", "", "rOcK");
    Song song7("","","Jazz");
    Song song8("","","EDM");
    Song testArray2[3] = {song6, song7, song8};
    int numSongs2 = 3;

    cout << frequentGenreSongs(testArray2, numSongs2) << endl;
    cout << endl;

    // Invalid number of songs test
    Song testArray3[5];
    int numSongs3 = -1;

    cout << frequentGenreSongs(testArray3, numSongs3) << endl;


    return 0;
}