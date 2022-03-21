// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 7 - Problem #3
#include <iostream>

using namespace std;

class Song {

    public:
        Song();     // Default constructor
        Song(string titleInitial, string artistInitial, string genreInitial);       // Parameterized constructor

        // Getter member functions
        string getTitle() const;            // Returns the title of the song
        string getArtist() const;           // Returns the artist of the song
        string getGenre() const;            // Returns the genre of the song

        // Setter member functions
        void setTitle(string titleInput);   // Sets the title of the song
        void setArtist(string artistInput); // Sets the artist of the song
        void setGenre(string genreInput);   // Sets the genre of the song

    private:
        string title;   // Stores the title of the song object
        string artist;  // Stores the artist of the song object
        string genre;   // Stores the genre of the song object

};