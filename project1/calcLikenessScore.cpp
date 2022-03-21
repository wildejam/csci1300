// CSCI1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project 1 - Problem #4

/* Problem: 
Write a function called calcLikenessScore() that is going to find the Likeness Score (as described earlier)
between two sequences of equal length.
*/

#include <iostream>

using namespace std;


/* 
calcLikenessScore() - takes in 2 strings of equal length and prints the likeness score for them, with respect to the card game. 
If strings are not equal, returns -1.
Parameters: 
seq1 - The first sequence to be compared (string)
seq2 - The second string to be compared to (string)
Returns: likeness_score - The calculated likeness score (double)
*/
double calcLikenessScore(string seq1, string seq2) {
    // Initialize variables for number of cards, number of cards with same suit, number of cards with same suit and rank, and likeness score.
    double numberOfCards = seq1.length() / 2;
    double sameSuit = 0;
    double sameSuitRank = 0;
    double likeness_score = 0;

    // If the sequences are of the same length,
    if (seq1.length() == seq2.length()) {

        // Traverse sequence 1 by 2's; Traverse the suit of each card
        for (int i = 0; i < seq1.length() - 1; i = i + 2){

            // Read the suit. If the suit of the card is the same as that of the second sequence,
            if (seq1[i] == seq2[i]) {
                // Add one to the number of cards we have with the same suit
                sameSuit++;

                // Also, read the rank of the card, and if they match, add one to number of cards we have with same rank
                if (seq1[i + 1] == seq2[i + 1]) {
                    sameSuitRank++;
                }
            }
        }
        // When finished traversing the cards, calculate and return the likeness score.
        likeness_score = (sameSuit / numberOfCards) + (1 * sameSuitRank);
        return likeness_score;
    }

    // If the sequences are not the same length, return -1.
    else {
        return -1;
    }
}

// Main function used for testing calcLikenessScore()
int main() {
    string sequence1;
    string sequence2;
    cout << "Sequence 1: ";
    cin >> sequence1;
    cout << "Sequence 2: ";
    cin >> sequence2;

    cout << "Likeness Score: " << calcLikenessScore(sequence1, sequence2) << endl;

    return 0;
}