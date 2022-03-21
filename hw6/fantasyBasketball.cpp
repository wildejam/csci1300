// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 6 - Problem #3

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/*
split(): Takes in a string and a delimiter character, splits the string into sections separated by the delimiter character, and
    populates an array with the split pieces of the string. Returns the number of pieces the string was split into. Returns
    -1 if the number of split pieces is larger than the size of the array.
Parameters:
    str - The string to be split (string)
    delimiter - The designated delimiter character (char)
    arr[] - The array where the split pieces of the string will be stored (string)
    arraySize - The size of the pieces[] array (int)
Returns: pieceCounter - The number of pieces that the string was split into (int)
*/
int split(string str, char delimiter, string arr[], int arraySize) {
    // Initialize variables for number of pieces, current position of arr[], stringLength, and temporary variable to hold a piece of a string
    int pieceCounter = 0;
    int arrayPos = 0;
    int stringLength = str.length();
    string piece;

    // Traverse the string, one character at a time
    for (int i = 0; i < stringLength; i++) {

        // If the traversal lands on the delimiter character OR the end of the string is reached...
        if (str[i] == delimiter || i == stringLength - 1) {

            // ...if this if statement was triggered by the end of the string being reached, add the final character to piece...
            if (i == stringLength - 1) {
                piece = piece + str[i];
            }

            // ... and add the current string as an array element to arr[], and reset piece to be empty. 
            // Also add 1 to the number of pieces in arr[].
            arr[arrayPos] = piece;
            arrayPos++;
            piece = "";
            pieceCounter++;


        }
        // Else, if the current string character is not equal to the delimiter, add the character to piece
        else {
            piece = piece + str[i];
        }
    }

    // If the inputted string was empty, exit the function and return 0.
    if (str == "") {
        return 0;
    }

    // If the number of pieces fits into the alotted size of the array, return pieceCounter
    if (pieceCounter <= arraySize) {
        return pieceCounter;
    }
    // Else if the number of pieces exceeds the allotted array size, return -1
    else {
        return -1;
    }
}

/*
calcUsg() - Takes in an array of playerStats and the size of the array, and returns the usage percentage of that player
Parameters:
    playerStats[] - The array of player stats. Information should be formatted like it is in the example txt files in the problem.
    arraySize - The size of the playerStats array
Returns: 
    usgPercentage - The usage percentage of the player based on the information passed into the function
    Returns -1 if the size of the array is anything other than 14. This function is only to be used for the basketball starters.    
*/
double calcUsg(string playerStats[], int arraySize) {
    // Only use this function if arraySize == 14. This function should only be used to calculate usg of basketball players with 14 stat elements
    if (arraySize == 14) {
        // Assign variables to all of the stats as given by the array of player information
        double usgPercentage = 0;
        double mp = stod(playerStats[2]);
        double fga = stod(playerStats[4]);
        double fta = stod(playerStats[8]);
        double tov = stod(playerStats[9]);
        double tmmp = stod(playerStats[10]);
        double tmfga = stod(playerStats[11]);
        double tmfta = stod(playerStats[12]);
        double tmtov = stod(playerStats[13]);

        usgPercentage = 100 * (((fga + 0.44 * fta + tov) * (tmmp / 5)) / (mp * (tmfga + 0.44 * tmfta + tmtov)));
        
        return usgPercentage;
    }
    // If the passed in array has a size other than 14, it must not be a valid basketball player stat list. Return -1.
    else {
        return -1;
    }
}

/*
calcTs() - Takes in an array of playerStats and the size of the array, and returns the true shooting percentage of that player
Parameters:
    playerStats[] - The array of player stats. Information should be formatted like it is in the example txt files in the problem.
    arraySize - The size of the playerStats array
Returns: 
    tsPercentage - The usage percentage of the player based on the information passed into the function
    Returns -1 if the size of the array is anything other than 5. This function is only to be used for the basketball bench players.    
*/
double calcTs(string playerStats[], int arraySize) {
    // Only use this function if arraySize == 5. This function should only be used to calculate usg of basketball players with 5 stat elements 
    if (arraySize == 5) {
        // Assign variables to all needed stats as given by the array of player information
        double tsPercentage = 0;
        double pts = stod(playerStats[2]);
        double fga = stod(playerStats[3]);
        double fta = stod(playerStats[4]);

        // Calculate tsa
        double tsa = fga + (0.44 * fta);
        // Calculate the TS %
        tsPercentage = 100 * (pts / (2 * tsa));
        // Return TS %
        return tsPercentage;
    }

    // If the passed in array has a size other than 14, it must not be a valid basketball player stat list. Return -1.
    else {
        return -1;
    }


}

int main() {
    // Declare variables
    string startersFileName;    // Stores the filename of starters that the user will input
    string benchFileName;       // Stores the filename of bench players that the user will input
    string chosenStarters[5];   // Stores the chosen starter players. Each element has the name, role, and team. Used for printing
    string chosenBenches[3];    // Stores the chosen bench players. Each element has the name, role, and team. Used for printing
    string line;                // Stores the current line, when documents are read
    string playerInfo[14] ;     // Stores the information for the player currently being read in a file
    int startersCounter = 0;    // Counts the number of starters that have been chosen
    int benchCounter = 0;       // Counts the number of bench players that have been chosen
    ifstream startersFile;      // Stream used to read the starters file
    ifstream benchFile;         // Stream used to read the bench players file

    // Prompt and get input for the filenames of the starters and bench players files
    cout << "Enter the filename of starters: " << endl;
    cin >> startersFileName;
    cout << "Enter the filename of bench players: " << endl;
    cin >> benchFileName;

    // Open the files that the user inputted
    startersFile.open(startersFileName);
    benchFile.open(benchFileName);

    // If and only if BOTH of the files were successfully opened,
    if (startersFile.is_open() && benchFile.is_open()) {

        // Read the starter file, line by line, until either the document ends or 5 starters have been chosen
        while (getline(startersFile, line) && startersCounter < 5) {

            // Only process the line if it is actual input; not the first line that shows what each value represents
            if (line != "Player,team,Minutes played,field goals,field goals attempted,3 pointers,3 pointers attempted,free throws,"
            "free throws attempted,turnovers,team minutes played,team field goals attempted,team free throws attempted,"
            "team turnovers") {

                // Fill playerInfo[] with the information about the starter, as given by the current line being read in the document
                split(line, ',', playerInfo, 14);

                // If the starter whose line is currently being read has a usg % greater than 28%,
                if (calcUsg(playerInfo, 14) > 28) {
                    // Fill the chosenStarters array at the position indicated by the counter with the name, role, and team, and increment counter
                    chosenStarters[startersCounter] = playerInfo[0] + ", starter , " + playerInfo[1];
                    startersCounter++;
                }

            }
        }

        // Read the bench file, line by line, until either the document ends or 8 total players have been chosen
        while (getline(benchFile, line) && benchCounter < 3) {

            // Only process the line if it is actual input; not the first line that shows what each value represents
            if (line != "Player,Tm,PTS,FGA,FTA") {

                // Fill playerInfo[] with the information about the bench player, as given by the current line being read in the document
                split(line, ',', playerInfo, 5);

                // If the bench player whose line is currently being read has a tsa % greater than 50%,
                if (calcTs(playerInfo, 5) > 50) {
                    // Fill the chosenBenches array at the position indicated by the counter with the name, role, and team, and increment counter
                    chosenBenches[benchCounter] = playerInfo[0] + ", bench, " + playerInfo[1];
                    benchCounter++;
                }
            }
        }

        // After reading the files, print out the chosen players to the console
        cout << "Selected Players: " << endl;
        for (int i = 0; i < startersCounter; i++) {
            cout << chosenStarters[i] << endl;
        }
        for (int i = 0; i < benchCounter; i++) {
            cout << chosenBenches[i] << endl;
        }

        // If there were a sufficient amount of players to form a team, print a success message. If not, print a failure message.
        if (startersCounter == 5 && benchCounter == 3) {
            cout << "Great, your team is ready! " << endl;
        }
        else {
            cout << "Not enough players who satisfy the criteria to form a team! " << endl;
        }
    }

    // If one or more of the files were not successfully opened, print an error message
    else {
        cout << "Could not open file(s). " << endl;
    }


    return 0;
}