// CSCI1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 5 - Problem #1

#include <iostream>

using namespace std;

int main() {
    // Create the distance array and populate it with 10 elements, with each one holding "42.42"
    double distance[10];
    for (int i = 0; i < 10; i++) {
        distance[i] = 42.42;
    }
    // Print the array
    for (int i = 0; i < 10; i++) {
        cout << distance[i] << endl;
    }
    cout << endl;

    // Create the pasta array and populate it with 5 elements, each one representing a type of pasta
    string pasta[5] = {"Penne", "Bucatini", "Farfalle", "Fusilli", "Rigatoni"};
    // Print the array
    for (int i = 0; i < 5; i++) {
        cout << pasta[i] << endl;
    }
    cout << endl;
    
    // Create the sequence array and populate it with the first 200 positive odd integers in order
    int sequence[100];
    for (int i = 0; i < 100; i++) {
        sequence[i] = 2 * i + 1;
    }
    // Print the array
    for (int i = 0; i < 100; i++) {
        cout << sequence[i] << endl;
    } 
    cout << endl;

    // Create the letters array and populate it with all uppercase and lowercase letters in order, using the ASCII table
    // Letters[] should have a size of 52 to account for every lowercase and uppercase letter
    char letters[52];
    // Traverse letters[] and fill it
    for (int i = 0; i < 52; i++) {
        // If i is on an even number, print the corresponding capital letter
        if (i % 2 == 0) {
            letters[i] = char((i / 2) + 65);
        }
        // If i is on an odd number, print the corresponding lowercase letter
        if (i % 2 == 1 || i == 1) {
            letters[i] = char((i / 2) + 97);
        }
        // We use "i / 2" to accomodate for the fact that each letter takes up 2 elements; one for the capital and one for the lowercase.
    }
    // Print the array
    for (int i = 0; i < 52; i++) {
        cout << letters[i] << endl;
    }
    cout << endl;
    return 0;
}