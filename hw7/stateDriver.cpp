// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 7 - Problem #1
#include "state.h"
#include <iostream>

using namespace std;

using namespace std;

/*
Template for writing test cases taken from hw7 canvas page
Expected output:
State name: 
Population: 0
Size: 0 square miles
State Name: Nebraska
State population: 1951996
Size: Size: 53280 square miles
State name: Nebraska
Population: 1951996
Size: 77348 square miles
Population density: 25.2365 people per square mile


State name: The people's republic of ardinbourough state
Population: 5
Size: 0 square miles
Population density: 0
*/
int main(){
    // Test default constructor and get functions
    State s1 = State();
    cout << "State name: " << s1.getName() << endl;
    cout << "Population: " << s1.getPopulation() << endl;
    cout << "Size: " << s1.getSquareMileage() << " square miles" << endl;

    // Test state name setter
    string name = "Nebraska";
    s1.setName(name);
    cout << "State Name: " << s1.getName() << endl; 

    // Test population setter
    int population = 1951996;
    s1.setPopulation(population);
    cout << "State population: " << s1.getPopulation() << endl;

    // Test square mileage setter
    int squareMileage = 53280;
    s1.setSquareMileage(squareMileage);
    cout << "Size: " << s1.getSquareMileage() << " square miles" << endl;

    // Test parameterized constructor
    int squareMileage2 = 77348;
    State s2 = State(name, population, squareMileage2);
    cout << "State name: " << s2.getName() << endl; 
    cout << "Population: " << s2.getPopulation() << endl;
    cout << "Size: " << s2.getSquareMileage() << " square miles" << endl;

    // Test population density
    cout << "Population density: " << s2.getPopulationDensity() << " people per square mile" << endl;


    cout << endl << endl;


    // Divide by 0 test
    State s4 = State();
    string name2 = "The people's republic of ardinbourough state";
    int population2 = 5;
    s4.setName(name2);
    s4.setPopulation(population2);
    cout << "State name: " << s4.getName() << endl;
    cout << "Population: " << s4.getPopulation() << endl;
    cout << "Size: " << s4.getSquareMileage() << " square miles" << endl;
    cout << "Population density: " << s4.getPopulationDensity() << endl;

}