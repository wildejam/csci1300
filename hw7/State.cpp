// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 7 - Problem #1
#include "State.h"
#include <iostream>

using namespace std;

// Default Constructor for State class. Sets state name to empty string, population to 0, and square mileage to 0
State::State() {
    stateName = "";
    population = 0;
    squareMileage = 0;
}

// Parameterized Constructor for State class. Sets name, population, and square mileage to user-inputted values
State::State(string initialStateName, int initialPopulation, int initialSquareMileage) {
    stateName = initialStateName;
    population = initialPopulation;
    squareMileage = initialSquareMileage;
}

// Returns the name of the state
string State::getName() const {
    return stateName;
}

// Returns the population of the state
int State::getPopulation() const {
    return population;
}

// Returns the square mileage of the state
int State::getSquareMileage() const {
    return squareMileage;
}

// Calculates and returns the population density of the state
double State::getPopulationDensity() const {

    // This if statement accounts for a divide by 0 error; if the square mileage is 0, simply return 0
    if (squareMileage == 0) {
        return 0;
    }
    // Multiply by 1.0 to get a decimal answer
    else {
        return (population * 1.0 / squareMileage * 1.0);
    }
}

// Sets the name of the state to the input
void State::setName(string nameInput) {
    stateName = nameInput;
}

// Sets the population of the state to the input
void State::setPopulation(int populationInput) {
    population = populationInput;
}

// Sets the square mileage of the state to the input
void State::setSquareMileage(int squareMileageInput) {
    squareMileage = squareMileageInput;
}
