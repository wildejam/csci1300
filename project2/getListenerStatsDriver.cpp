// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project 2 - Problem #10

#include <iostream>
#include <iomanip>
#include "Listener.h"

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

// Main function for testing getListenerStats()
/* Expected Output:
Listener2 listened to 2 songs.
Listener2's average number of listens was 4.00
1
Listener3 has not listened to any songs.
0
Listener4 does not exist.
-3
*/
int main() {
    // Setup
    // Creating 3 listeners
    Listener listeners[3];
    // Setting listenerName and num listens for Listener1
    listeners[0].setListenerName("Listener1");
    listeners[0].setPlayCountAt(0,1);
    listeners[0].setPlayCountAt(1,4);
    listeners[0].setPlayCountAt(2,2);
    // Setting listenerName and num listens forListener2
    listeners[1].setListenerName("Listener2");
    listeners[1].setPlayCountAt(0,0);
    listeners[1].setPlayCountAt(1,5);
    listeners[1].setPlayCountAt(2,3);
    // Setting listenerName and num listens forListener3
    listeners[2].setListenerName("Listener3");
    listeners[2].setPlayCountAt(0,0);
    listeners[2].setPlayCountAt(1,0);
    listeners[2].setPlayCountAt(2,0);

    // Normal case test
    cout << getListenerStats("Listener2", listeners, 3, 3) << endl;
    // Edge case test: listener hasn't listened to any songs
    cout << getListenerStats("Listener3", listeners, 3, 3) << endl;
    // Edge case test: listener name doesn't exist
    cout << getListenerStats("Listener4", listeners, 3, 3) << endl;
}