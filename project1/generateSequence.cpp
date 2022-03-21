// CSCI1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project 1 - Extra Credit Question #1

/* Problem:
The challenge is to randomly create a sequence of the cards when the number of cards making up the sequence is given.
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

/* 
generateSequence() - Takes in a number of cards and prints a random sequence of that many cards.
Parameters: numOfCards - Number of cards forming the sequence (int)
Returns: generated_seq - The random sequence of cards (string)
*/
string generateSequence(int numOfCards) {

    const string SUITS = "SCDH";
    const string RANKS = "A123456789JQK";
    string suit;
    string rank;
    string generatedSequence;

    // Traverse the sequence 2 characters at a time, until the total number of characters is reached
    for (int i = 0; i < numOfCards * 2; i = i + 2) {

        // Generate random suits and ranks, and add them to the entire generatedSequence
        suit = SUITS[rand() % 3];
        rank = RANKS[rand() % 12];
        generatedSequence = generatedSequence + suit + rank;

    }

    return generatedSequence;
}

// Main function for testing generateSequence(). Note that srand(time(0)) is in the main function
int main() {
    srand(time(0));
    int numberOfCards = 0;
    cout << "Number of cards: ";
    cin >> numberOfCards;

    cout << generateSequence(numberOfCards) << endl;

    return 0;
}