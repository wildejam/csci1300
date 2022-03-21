// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 7 - Problem #1

#include <iostream>

using namespace std;

class State {

    public:
        // Constructors
        State();
        State(string initialStateName, int initialPopulation, int initialSquareMileage);
        
        // Getters
        string getName() const;                 // Returns the name of the state
        int getPopulation() const;              // Returns the population of the state
        int getSquareMileage() const;           // Returns the square mileage of the state
        double getPopulationDensity() const;    // Calculates and returns the population density of the state

        // Setters
        void setName(string nameInput);                 // Sets the name of the state
        void setPopulation(int populationInput);        // Sets the population of the state
        void setSquareMileage(int squareMileageInput);  // Sets the square mileage of the state


    private:
        string stateName;   // Name of the state
        int population;     // Population of the state
        int squareMileage;  // Square mileage of the state
};