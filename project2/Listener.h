// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project 2 - Problem #6

#include <iostream>

using namespace std;

#ifndef LISTENER_H
#define LISTENER_H

class Listener {

    public:
        // Constructors
        Listener();     // Default Constructor
        Listener(string initialListenerName, int initialPlayCount[], int initialArraySize);  // Parameterized Constructor

        // Getters
        string getListenerName();                   // Returns the name of the listener
        int getPlayCountAt(int index);              // Returns the play count at an index of playCount[]. Returns -1 if index parameter is invalid
        int totalPlayCount();                       // Returns the total play count of all of the songs
        int getNumUniqueSongs();                    // Returns number of unique songs listened to by the listener; songs with at least 1 listen
        int getSize();                              // Returns the value of size, which is the size of playCount[]

        // Setters
        void setListenerName(string inputName);     // Sets the name of the listener
        bool setPlayCountAt(int index, int value);  // Sets the play count of a song at a specific index. Returns false if it fails

    private:
        static const int size = 50;     // Size of playCount[]. Is always 50. Constant.
        string listenerName;            // The name of the listener
        int playCount[size];            // The array that stores the number of listens of each song for the listener
};

#endif