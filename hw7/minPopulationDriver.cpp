// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 7 - Problem #2
#include "State.h"
#include <iostream>

using namespace std;



/*
minPopulation() - takes in an array of State objects and returns the index value of the object with the smallest population
Parameters:
    states[] - The array of state objects to be processed (State)
    size - The size of the states[] array. (int)
Returns: 
    smallestStateIndex - The index of the state with the smallest population (int)
    Returns -1 If the array is empty
*/
int minPopulation(State states[], int size) {
    int smallestStateIndex = 0;     // variable used to store the index of the state with the smallest population. Initialize to 0.
    int statesCounter = 0;          // used to store the number of states that have been counted (for checking for empty arrays)


    // Traverse the array
    for (statesCounter = 0; statesCounter < size; statesCounter++) {
        // If the population of the current state is less than that of the population of the state indicated by the smallest state index,
        if (states[statesCounter].getPopulation() < states[smallestStateIndex].getPopulation()) {
            // The smallest state occurs at position i in the array.
            smallestStateIndex = statesCounter;
        }
    }

    // If the states[] array was empty, return -1
    if (statesCounter == 0) {
        return -1;
    }

    // If the states[] array was not empty, return the index of the state with smallest population
    else {
        return smallestStateIndex;
    }
}



// Main function used for testing. Testing code is from the assignment sheet on canvas
int main() {

    State states[5];
    states[0] = State("Colorado", 5893634, 104094);
    states[1] = State("California", 39613493,
    163695);
    states[2] = State("Nebraska", 1951996, 77348);
    int index = minPopulation(states, 3);
    cout << states[index].getName() << endl;
    cout << states[index].getPopulation() << endl;
    cout << states[index].getPopulationDensity() << endl;

    cout << endl;

    // Test case for empty arrays
    State states2[5];
    states2[0] = State();
    states2[1] = State();
    states2[2] = State();
    int index2 = minPopulation(states, 3);
    cout << states[index2].getName() << endl;
    cout << states[index2].getPopulation() << endl;
    cout << states[index2].getPopulationDensity() << endl;

    return 0;
}