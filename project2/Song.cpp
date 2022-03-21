// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project 2 - Problem #1
#include <iostream>
#include "Song.h"

using namespace std;

// Default constructor for song class. Sets title, artist, and genre to empty strings
Song::Song() {
    title = "";
    artist = "";
    genre = "";
}

// Parameterized constructor for song class
Song::Song(string titleInitial, string artistInitial, string genreInitial) {
    title = titleInitial;
    artist = artistInitial;
    genre = genreInitial;
}

// Getter function for getting the title
string Song::getTitle() const {
    return title;
}

// Getter function for getting the artist
string Song::getArtist() const {
    return artist;
}

// Getter function for getting the genre
string Song::getGenre() const {
    return genre;
}

// Setter function for setting the title
void Song::setTitle(string titleInput) {
    title = titleInput;
}

// Setter function for setting the artist
void Song::setArtist(string artistInput) {
    artist = artistInput;
}

// Setter function for setting the genre
void Song::setGenre(string genreInput) {
    genre = genreInput;
}


