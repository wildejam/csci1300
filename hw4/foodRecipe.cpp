// CSCI1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 4 - Problem #3

// Problem: Create a sandwich recipe menu that says if you can make a certain type of sandwich when given ingredients.

/* Algorithm:
    Initialize variables:
        desiredSandwich (int)
        ingredient1 (int)
        ingredient2 (int)
        ingredient3 (int)
        ingredient4 (double)

    While the user wishes to not quit (desiredSandwich != Quit):

        Prompt user and get input for desiredSandwich

            If desiredSandwich == BLT:
                Prompt and get input for BLT ingredients
                If ingredients are sufficient:
                    Print "You can make a BLT."
                Else
                    Print "You don't have enough for a BLT."
            Else If desiredSandwich == caprese:
                Prompt and get input for caprese ingredients
                If ingredients are sufficient:
                    Print "You can make a caprese sandwich."
                Else
                    Print "You don't have enough for a caprese sandwich."
            Else If desiredSandwich == veggie:
                Prompt and get input for veggie ingredients
                If ingredients are sufficient:
                    Print "You can make a veggie sandwich."
                Else
                    Print "You don't have enough for a veggie sandwich."
            Else
                Print "Invalid input."      
    
    Print "Goodbye!"
*/

#include <iostream>

using namespace std;

int main() {
    // Initialize Variables
    int desiredSandwich = 0;
    int ingredient1 = 0;
    int ingredient2 = 0;
    double ingredient3 = 0.0;
    double ingredient4 = 0.0;

    // While the user does not wish to quit, ask them for ingredients and run the program
    while (desiredSandwich != 4) {

        // Prompt user and get input for Desired Sandwich, or Quit the program
        cout << 
            "Select a numerical option: \n"
            "=== menu === \n"
            "1. BLT \n"
            "2. Caprese \n"
            "3. Veggie \n"
            "4. Quit"
        << endl;        
        cin >> desiredSandwich;

        // If the user wants a BLT
        if (desiredSandwich == 1){

            // Prompt for and get input for ingredients
            cout << "How many bacon strips do you have? " << endl;
            cin >> ingredient1;
            cout << "How many tomato slices do you have? " << endl;
            cin >> ingredient2;
            cout << "How many lettuce leaves do you have? " << endl;
            cin >> ingredient3;
            cout << "How many ounces of mayonnaise do you have? " << endl;
            cin >> ingredient4;

            // Compute if desired sandwich is possible with the given ingredients
            if (ingredient1 >= 4 && ingredient2 >= 3 && ingredient3 >= 2.0 && ingredient4 >= 0.51) {
                cout << "You can make a BLT. " << endl;
            }
            else {
                cout << "You don't have enough for a BLT. " << endl;
            }
        }

        // If the user wants a Caprese sandwich
        else if (desiredSandwich == 2){

            // Prompt for and get input for ingredients
            cout << "How many mozzarella slices do you have? " << endl;
            cin >> ingredient1;
            cout << "How many tomato slices do you have? " << endl;
            cin >> ingredient2;
            cout << "How many basil leaves do you have? " << endl;
            cin >> ingredient3;
            cout << "How many ounces of balsamic glaze do you have? " << endl;
            cin >> ingredient4;

            // Compute if desired sandwich is possible with the given ingredients
            if (ingredient1 >= 4 && ingredient2 >= 2 && ingredient3 >= 9.0 && ingredient4 >= 0.12) {
                cout << "You can make a caprese sandwich. " << endl;
            }
            else {
                cout << "You don't have enough for a caprese sandwich. " << endl;
            }
        }

        // If the user wants a veggie sandwich
        else if (desiredSandwich == 3){

            // Prompt for and get input for ingredients
            cout << "How many red onion rings do you have? " << endl;
            cin >> ingredient1;
            cout << "How many cucumber slices do you have? " << endl;
            cin >> ingredient2;
            cout << "How many ounces of diced roasted pepper do you have? " << endl;
            cin >> ingredient3;
            cout << "How many ounces of hummus do you have? " << endl;
            cin >> ingredient4;

            // Compute if desired sandwich is possible with the given ingredients
            if (ingredient1 >= 5 && ingredient2 >= 7 && ingredient3 >= 2.33 && ingredient4 >= 2.5) {
                cout << "You can make a veggie sandwich. " << endl;
            }
            else {
                cout << "You don't have enough for a veggie sandwich. " << endl;
            }
        }

        // If the user inputs 4, the program terminates with a goodbye message
        else if (desiredSandwich == 4){
            cout << "Goodbye!" << endl;
        }

        // If the user input any value other than 1, 2, 3, or 4, print "Invalid input."
        else {
            cout << "Invalid input." << endl;
        }

    }

    return 0;
}