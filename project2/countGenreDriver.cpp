// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project 2 - Problem #4

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

// main() used for testing toLower() and countGenre()
/* Expected Output:
lol
epic
this is ridiculous
#$%*1123cdesijsdfio

2
0
*/
int main() {

    // Testing for toLower() with different test cases
    string string1 = "LOL";
    string string2 = "Epic";
    string string3 = "ThIs iS rIdICUlOus";
    string string4 = "#$%*1123CDESIjsdfio";

    cout << toLower(string1) << endl;
    cout << toLower(string2) << endl;
    cout << toLower(string3) << endl;
    cout << toLower(string4) << endl;

    cout << endl;

    // Testing for countGenre().
    Song songTest1;
    Song songTest2;
    Song songTest3;
    Song songTest4;
    Song songTest5;
    songTest1.setGenre("Pop");
    songTest2.setGenre("Jazz");
    songTest3.setGenre("EDM");
    songTest4.setGenre("Jazz");
    songTest5.setGenre("Pop");
    Song songTestArray1[5] = {songTest1, songTest2, songTest3, songTest4, songTest5};
    Song songTestArray2[0];
    int size1 = 5;
    int size2 = 0;

    cout << countGenre("Jazz", songTestArray1, size1) << endl;  // Normal test case
    cout << countGenre("Pop", songTestArray2, size2) << endl;   // Test case for empty arrays
    
    return 0;
}