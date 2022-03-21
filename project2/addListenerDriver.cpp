// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project 2 - Problem #9

#include <iostream>
#include <string>
#include "Listener.h"

using namespace std;

/*
toLower() - Takes in a string and returns the same string but all lowercase. Used for making countGenre case insensitive.
Parameters: str - The inputted string to be made lowercase
Returns: newStr - The output string which should be the same as string but in lowercase.
*/
string toLower(string str) {
    // Variable used to store new string. Initialize it to be the inputted string
    string newStr = str;
    int strLength = str.length();

    // Traverse the inputted string
    for (int i = 0; i < strLength; i++) {

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

// Main function for testing addListener()
/* Expected output:
Ninja
Knuth
0
-2
Knuth
3

0
*/
int main() {
    // Edge case test: listeners[] is full

    Listener listeners[1];
    int numSongs = 50;
    int listenersArrSize = 1;
    listeners[0].setListenerName("Ninja");
    // Add 5 songs listened to by the listener “Ninja”
    for(int i=0; i<5; i++) {
        listeners[0].setPlayCountAt(i, 1);
    }
    int numListenersStored = 1;
    int val = addListener("Knuth", listeners, numSongs, numListenersStored, listenersArrSize);
    // Print the array
    for(int i=0; i<numListenersStored; i++) {
        cout<<listeners[i].getListenerName()<<endl;
    }

    // Normal case test: listeners[] has sufficient space and name parameter is not an empty string
    Listener listeners2[10];
    int listenersArrSize2 = 10;
    int numListenersStored2 = 0;
    int numSongs2 = 50;
    int val2 = addListener("Knuth", listeners2, numSongs2, numListenersStored2, listenersArrSize2);
    // Print name and listens of the added listener
    cout<<listeners2[0].getListenerName()<<endl;
    cout<<listeners2[0].getPlayCountAt(0)<<endl;

    // Edge case test: Adding a listener whose name already exists in the array
    Listener listeners3[10];
    int listenersArrSize3 = 10;
    int numSongs3 = 5;
    listeners3[0].setListenerName("Knuth");
    // Add listens for 5 songs for listener “Knuth”
    for(int i=0; i<5; i++) {
        listeners3[0].setPlayCountAt(i, i);
    }
    int numListenersStored3 = 1;
    cout<<addListener("Knuth", listeners3, numSongs3, numListenersStored3, listenersArrSize3)<<endl;
    // Code to print the listenerName and song three
    cout<<listeners3[0].getListenerName()<<endl;
    cout<<listeners3[0].getPlayCountAt(3)<<endl;
    cout<<listeners3[1].getListenerName()<<endl;
    cout<<listeners3[1].getPlayCountAt(3)<<endl;

    return 0;
}