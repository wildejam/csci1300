// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project 2 - Problem #6

#include <iostream>
#include "Listener.h"

using namespace std;

// Default constructor. Sets listenerName to empty string and all values of playCount[] to 0
Listener::Listener() {
    listenerName = "";
    for (int i = 0; i < size; i++) {
        playCount[i] = 0;
    }
}

// Parameterized constructor. Sets listenerName to the input and takes in an array to populate playCount.
// Disregards extra numbers if the inputted array is larger than playCount[]. Fills extra values of playCount[] with 0's if inputted array is smaller.
Listener::Listener(string initialListenerName, int initialPlayCount[], int initialArraySize) {
    // Set listenerName equal to the input
    listenerName = initialListenerName;

    // If the inputted array's size is larger than or equal to the size of playCount[],
    if (initialArraySize >= size) {
        // Fill playCount[] with the first values of the inputted array, and disregard the rest, if the inputted array is larger.
        for (int i = 0; i < size; i++) {
            playCount[i] = initialPlayCount[i];
        }
    }

    // If the inputted array is smaller than playCount[],
    else {
        // Populate playCount[] with the values stored in the inputted array,
        for (int i = 0; i < initialArraySize; i++) {
            playCount[i] = initialPlayCount[i];
        }
        // And then populate playCount[] with 0's for the remaining values
        for (int j = initialArraySize; j < size; j++) {
            playCount[j] = 0;
        }
    }
}

// Returns the name of the listener
string Listener::getListenerName() {
    return listenerName;
}

// Returns the play count at the inputted index. Returns -1 if the inputted index is less than 0 or greater than size
int Listener::getPlayCountAt(int index) {
    // If the inputted index is valid,
    if (index >= 0 && index < size) {
        return playCount[index];
    }

    // Else, if the inputted index is less than 0 or greather than or equal to the size of the array, return -1.
    else {
        return -1;
    }
}

// Returns the total play count of all of the songs
int Listener::totalPlayCount() {
    int sum = 0;    // Variable used to store the sum
    // Traverse playCount and add each element together
    for (int i = 0; i < size; i++) {
        sum += playCount[i];
    }
    return sum;     // Then return the sum
}

// Returns the number of unique songs listened to by the listener; returns number of songs with at least one listen
int Listener::getNumUniqueSongs() {
    int counter = 0;    // Counter variable used to store the number of songs with at least one listen
    // Traverse playCount[], and increment counter whenever a song is found with at least 1 listen
    for (int i = 0; i < size; i++) {
        if (playCount[i] > 0) {
            counter++;
        }
    }
    return counter;
}

// Returns the size of playCount[]
int Listener::getSize() {
    return size;
}

// Sets the listener name to the parameter value
void Listener::setListenerName(string inputName) {
    listenerName = inputName;
}

// Sets the play count at the given index to the given value. Returns true if the operation was completed successfully, and false if not.
bool Listener::setPlayCountAt(int index, int value) {
    // If the index and value parameters are valid, set playCount at that index to the value, and return true.
    if (index >= 0 && index < size && value > 0) {
        playCount[index] = value;
        return true;
    }
    // If either the index or the value are not valid inputs, do nothing and return false.
    else {
        return false;
    }
}