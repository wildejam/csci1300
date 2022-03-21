// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 7 - Problem #3
#include <iostream>
#include "Song.h"

using namespace std;

// Main function used for testing the implementation of the State class
/* Expected Output:
Song 1:   
Song 2 title: Rude Buster
Song 2 artist: Toby Fox
Song 2 genre: Funk
Song 1 new title: I've got Rhythm
Song 1 new artist: George Gershwin
Song 1 new genre: Jazz
*/
int main() {
    string song2Title = "Rude Buster";
    string song2Artist = "Toby Fox";
    string song2Genre = "Funk";

    // Test constructors
    Song song1 = Song();
    Song song2 = Song(song2Title, song2Artist, song2Genre);

    // Test default constructor
    cout << "Song 1: " << song1.getTitle() << " " << song1.getArtist() << " " << song1.getGenre() << endl;

    // Test getter member functions
    cout << "Song 2 title: " << song2.getTitle() << endl;
    cout << "Song 2 artist: " << song2.getArtist() << endl;
    cout << "Song 2 genre: " << song2.getGenre() << endl;

    // Test setter functions
    song1.setTitle("I've got Rhythm");
    song1.setArtist("George Gershwin");
    song1.setGenre("Jazz");

    cout << "Song 1 new title: " << song1.getTitle() << endl;
    cout << "Song 1 new artist: " << song1.getArtist() << endl;
    cout << "Song 1 new genre: " << song1.getGenre() << endl;
    
}