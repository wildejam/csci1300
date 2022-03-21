// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project 2 - Problem #3

#include <iostream>
#include "Song.h"

using namespace std;

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

// Main function used for testing
/* Expected Output:
Here is a list of songs 
Cotton Tail is by Duke Ellington
Hikaru Nara is by Goose House

No songs are stored
*/
int main() {
    // General Test
    Song songs2[2];
    songs2[0].setTitle("Cotton Tail");
    songs2[0].setArtist("Duke Ellington");
    songs2[0].setGenre("Jazz");
    songs2[1].setTitle("Hikaru Nara");
    songs2[1].setArtist("Goose House");
    songs2[1].setGenre("J-Pop");
    int numberOfSongsStored2 = 2;

    printAllSongs(songs2, numberOfSongsStored2);
    cout << endl;

    // Empty array test
    Song songs3[25];
    int numberOfSongsStored3 = 0;

    printAllSongs(songs3, numberOfSongsStored3);

    return 0;
}