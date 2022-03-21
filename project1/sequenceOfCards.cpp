// CSCI1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project 1 - Problem #7

/* Problem:
In this question, you will be writing a main() driver function through which you will give the end user the option
to choose from the following options:
●Calculate the Likeness Score between two sequences of equal length
●Find the Best Likeness Score between two sequences of unequal length
●Find the Winner among the sequences of 3 players and the Golden Sequence
●Exit
The menu will run on a loop, continually offering the user four options until they opt to quit.
You need to fill in the code for each of the options. Be sure to use the functions you wrote inquestions 4-6.
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


/*
bestLikenessScore() - Takes in a sequence and the golden sequence (which may not be equal length), calculates all the possible
likeness scores using calcLikenessScore, and returns the best possible score that the player could have.
Parameters: 
seq1 - The player's sequence which should be greater than or equal to the golden sequence (string)
gold_seq - The Golden Sequence (string)
Returns: best_likeness_score - The best possible likeness score (double)
*/
double bestLikenessScore(string seq1, string gold_seq) {
    string sequenceSubStr;
    double score = 0;
    double bestScore = 0;

    // If the player's sequence length is greater than or equal to the golden sequence length,
    if (seq1.length() >= gold_seq.length()) {

        // For the length indicated by the difference of the lenghts of seq1 and gold_seq, with i incrementing by 2 to simulate traversing each card,
        for (int i = 0; i <= seq1.length() - gold_seq.length(); i = i + 2) {

            // Calculate the likeness score between the substring of seq1 indicated by i, to the golden sequence
            score = calcLikenessScore(seq1.substr(i, gold_seq.length()), gold_seq);

            // If the current calculated score is greater than the current bestScore, update the bestScore to be the current score.
            if (score > bestScore) {
                bestScore = score;
            }
        }

        return bestScore;
    }
    // If the player's sequence length is less than the golden sequence length, return -1.
    else {
        return -1;
    }
}


/* 
findWinner() - Takes in 3 sequences and the golden sequence, and prints the winning sequence based on their similarity to the golden sequence.
    If there are ties, or every sequence has 0 points, prints special messages accordingly.
Parameters:
    seq1 - The first player's sequence
    seq2 - The second player's sequence
    seq3 - The third player's sequence
    gold_seq - The golden sequence
Returns: Nothing
*/
void findWinner(string seq1, string seq2, string seq3, string gold_seq) {
    // Initialize variables for the scores of all 3 players
    double player1Score = 0;
    double player2Score = 0;
    double player3Score = 0;

    // Calculate the likeness scores of all 3 sequences
    player1Score = bestLikenessScore(seq1, gold_seq);
    player2Score = bestLikenessScore(seq2, gold_seq);
    player3Score = bestLikenessScore(seq3, gold_seq);

    // Depending on the results of the likeness scores, print the appropriate message that declares the winner
    if (player1Score > player2Score && player1Score > player3Score) {
        cout << "Congratulations Player 1! You have won!" << endl;
    }
    else if (player2Score > player1Score && player2Score > player3Score) {
        cout << "Congratulations Player 2! You have won!" << endl;
    }
    else if (player3Score > player1Score && player3Score > player2Score) {
        cout << "Congratulations Player 3! You have won!" << endl;
    }
    else if (player1Score == player2Score && player1Score > player3Score) {
        cout << "Congratulations Players 1 and 2! You have won!" << endl;
    }
    else if (player2Score == player3Score && player2Score > player1Score) {
        cout << "Congratulations Players 2 and 3! You have won!" << endl;
    }
    else if (player1Score == player3Score && player1Score > player2Score) {
        cout << "Congratulations Players 1 and 3! You have won!" << endl;
    }
    else if (player1Score == 0 && player2Score == 0 && player3Score == 0) {
        cout << "Better luck next time everyone!" << endl;
    }    
    else if (player1Score == player2Score && player1Score == player3Score) {
        cout << "Congratulations everyone! You have all won!" << endl;
    }
    // If somehow none of the above conditions are met, print an error message
    else {
        cout << "Error" << endl;
    }
}


/* 
The final main() function! Will print a menu that asks the user what they wish to do. The menu will be displayed each time until the user quits.
If the user presents an invalid input, prints "Invalid input. Choices between 1-4."
*/
int main() {
    int choice = 0;

    // While the user does not wish to quit:
    while (choice != 4) {
        // Print the menu
        cout <<
            "----Menu!----\n"
            "Choice 1: Calculate the Likeness Score between 2 strings of equal length.\n"
            "Choice 2: Calculate the Best Likeness Score between 2 sequences of possibly different length.\n"
            "Choice 3: Find winner among sequences of 3 players and a Golden Sequence.\n"
            "Choice 4: Exit.\n"
            "Enter your choice (1-4): "
        << endl;
        cin >> choice;

        // If the user chooses choice 1, run calcLikenessScore(), taking inputs from the user for the parameters as needed.
        if (choice == 1) {

            cout << "Enter Sequence 1" << endl;
            string seq1;
            cin >> seq1;
            cout << "Enter Sequence 2" << endl;
            string seq2;
            cin >> seq2;

            if (seq1.length() == seq2.length()) {
                cout << "Score: " << calcLikenessScore(seq1, seq2) << endl;
            }

            else {
                cout << "Invalid input. Sequences of different length. " << endl;
            }
        }

        // If the user chooses choice 2, run bestLikenessScore(), taking inputs from the user for the parameters as needed.
        else if (choice == 2) {

            cout << "Enter Sequence 1" << endl;
            string seq1;
            cin >> seq1;
            cout << "Enter Sequence 2" << endl;
            string seq2;
            cin >> seq2;

            cout << "Best Likeness Score: " << bestLikenessScore(seq1, seq2) << endl;

        }

        // If the user chooses choice 3, run findWinner(), taking inputs from the user for the parameters as needed.
        else if (choice == 3) {

            cout << "Enter Sequence of Player 1" << endl;
            string seq1;
            cin >> seq1;
            cout << "Enter Sequence of Player 2" << endl;
            string seq2;
            cin >> seq2;
            cout << "Enter Sequence of Player 3" << endl;
            string seq3;
            cin >> seq3;
            cout << "Enter Golden sequence" << endl;
            string gold_seq;
            cin >> gold_seq;

            findWinner(seq1, seq2, seq3, gold_seq);

        }

        // If the user wishes to quit, print "Exiting."
        else if (choice == 4) {
            cout << "Exiting." << endl;
        }

        // If the user's input is invalid, print "Invalid input. Choices between 1-4."
        else {
            cout << "Invalid Input. Choices between 1-4. " << endl;
        }
    }

    return 0;
}


