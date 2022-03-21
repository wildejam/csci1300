// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project #3

// This file is used to test the findFlavorText() function

#include <iostream>
#include <random>
#include <string>
#include <fstream>

using namespace std;

/*
findFlavorText() - Function that reads a document filled with flavor text in a particular format, and returns the desired text. Randomly chooses from different flavor text
    options in the text file. Takes in a filename and a string indicating the desired text. Returns a string of one of the desired texts, chosen at random.
    Returns "ERROR: FLAVOR TEXT FILE COULD NOT BE OPENED!" if the file could not be opened. Returns "ERROR: CREATURE/MERCHANT NAME NOT FOUND!" if the name could not be found in the file.
Parameters:
    textFileName - The name of the file containing the flavor text, in a specific format. (string)
    subjectName - The name of the creature or merchant for which flavor text is being searched (string)
    desiredTextType - A string indicating the type of text the user wishes to search for. (string)
        This type can be one of a few things:
        beginningbattle     - Returns the beginning battle text for the specific monster
        idle                - Returns one of the 3 idle texts for the specific monster
        attacker            - Returns one of the 2 attacker texts for the specific monster
        attacked            - Returns one of the 2 attacked texts for the specific monster
        befriended          - Returns one of the 2 befriended texts for the specific monster
        default             - Returns the default text for a specific merchant
        dialogue1           - Returns the first dialogue part for a specific merchant
        dialogue2           - Returns the second dialogue part for a specific merchant
        dialoguefinal       - Returns the final dialogue part for a specific merchant
        goodbye             - Returns the goodbye dialogue for a specific merchant
        notenoughmoney      - Returns the "not enough money" dialogue for a specific merchant
        invaliditem         - Returns the "invalid item" dialogue for a specific merchant
        If the desiredTextType is none of these, function returns "ERROR: INVALID DESIREDTEXTTYPE!"
Returns: A random dialogue of the desired type from the document.

*srand should be called in any function this is used in to generate truly random flavor text
*/
string findFlavorText(string textFileName, string subjectName, string desiredTextType) {
    // Declare variables
    ifstream flavorTextFile;                // Input filestream used to read flavor text file
    string line;                            // Stores the current line being read in the text file
    int lineSearchOffset = 0;               // Stores a value that is used to retrieve the desired line from the text file
    int textTypesIndex = -1;                // Stores the index of the desired text types as shown in the accepted text types array. Is used for the switch statement.
    int numberOfAcceptableTextTypes = 12;   // Stores the number of acceptable text types
    // Constant array used to store the acceptable desiredTextTypes
    const string acceptableDesiredTextTypes[numberOfAcceptableTextTypes] = {"beginningbattle", "idle", "attacker", "attacked", "befriended",
        "default", "dialogue1", "dialogue2", "dialoguefinal", "goodbye", "notenoughmoney", "invaliditem"};

    // Locate and store the index of the desiredTextType according to the acceptableDesiredTextTypes array. This is done so a switch statement can be used later.
    for (int i = 0; i < numberOfAcceptableTextTypes; i++) {
        if (desiredTextType == acceptableDesiredTextTypes[i]) {
            textTypesIndex = i;
        }
    }

    // If no match was found, the desiredTextType was invalid. Return an error string.
    if (textTypesIndex == -1) {
        return "ERROR: INVALID DESIREDTEXTTYPE!";
    }

    // Determine the getline offset value based on the desiredTextType. Set some offsets to be random for random flavor text selections.
    switch (textTypesIndex) {
        case 0: case 5:
            lineSearchOffset = 1;
            break;
        case 1:
            lineSearchOffset = 2 + (rand() % 3);
            break;
        case 2:
            lineSearchOffset = 5 + (rand() % 2);
            break;
        case 3:
            lineSearchOffset = 7 + (rand() % 2);
            break;
        case 4:
            lineSearchOffset = 9 + (rand() % 2);
            break;
        case 6:
            lineSearchOffset = 2;
            break;
        case 7:
            lineSearchOffset = 3;
            break;
        case 8:
            lineSearchOffset = 4;
            break;
        case 9:
            lineSearchOffset = 5;
            break;
        case 10:
            lineSearchOffset = 6;
            break;
        case 11:
            lineSearchOffset = 7;
            break;
        // An invalid desiredTextType should be impossible at this point, but if it occurs, return the error string.
        default:
            return "ERROR: INVALID DESIREDTEXTTYPE!";
            break;      
    }
    
    // Now that we've determined the getline offset, open the desired file.
    flavorTextFile.open(textFileName);

    // If the file could not be opened, return a string indicating such.
    if (flavorTextFile.fail()) {
        return "ERROR: FLAVOR TEXT FILE COULD NOT BE OPENED!";
    }

    // Once we have the file and the line search offset, we can locate our desired line of flavor text. Begin reading the file.
    while (getline(flavorTextFile, line)) {
        // Once a matching name has been found in the file,
        if (line == subjectName) {
            // getline() as many times as necessary to reach the desired flavor text line, using the previously calculated line offset. Return this value.
            for (int i = 0; i < lineSearchOffset; i++) {
                getline(flavorTextFile, line);
            }
            return line;
        }
    }

    // If there were no matching names in the file, return an error message indicating such.
    return "ERROR: CREATURE/MERCHANT NAME NOT FOUND!";
}

// This function is used to test the findFlavorTextDriver() function
int main() {
    srand(time(NULL));

    string merchantFile = "merchantFlavorText.txt";
    string monsterFile = "monsterFlavorText.txt";
    string fakeFile = "fakeFile.txt";

// {"beginningbattle", "idle", "attacker", "attacked", "befriended", "default", "dialogue1", "dialogue2", "dialoguefinal", "goodbye", "notenoughmoney", "invaliditem"};

    // Normal Tests: Merchant flavor texts
    cout << findFlavorText(merchantFile, "Professor Yeh", "default") << endl;
    cout << findFlavorText(merchantFile, "Professor Yeh", "dialogue1") << endl;
    cout << findFlavorText(merchantFile, "Professor Yeh", "dialogue2") << endl;
    cout << findFlavorText(merchantFile, "Professor Yeh", "dialoguefinal") << endl;
    cout << findFlavorText(merchantFile, "Professor Yeh", "goodbye") << endl;
    cout << findFlavorText(merchantFile, "Professor Yeh", "notenoughmoney") << endl;
    cout << findFlavorText(merchantFile, "Professor Yeh", "invaliditem") << endl;

    // Normal Tests: Monster flavor texts (also tests randomness)
    cout << findFlavorText(monsterFile, "Tuxedo Plant", "beginningbattle") << endl;
    cout << findFlavorText(monsterFile, "Tuxedo Plant", "idle") << endl;
    cout << findFlavorText(monsterFile, "Tuxedo Plant", "idle") << endl;
    cout << findFlavorText(monsterFile, "Tuxedo Plant", "idle") << endl;
    cout << findFlavorText(monsterFile, "Tuxedo Plant", "attacker") << endl;
    cout << findFlavorText(monsterFile, "Tuxedo Plant", "attacker") << endl;
    cout << findFlavorText(monsterFile, "Tuxedo Plant", "attacked") << endl;
    cout << findFlavorText(monsterFile, "Tuxedo Plant", "attacked") << endl;
    cout << findFlavorText(monsterFile, "Tuxedo Plant", "befriended") << endl;
    cout << findFlavorText(monsterFile, "Tuxedo Plant", "befriended") << endl;

    // Edge cases: file does not exist, name does not exist, and desiredTextType is invalid
    cout << findFlavorText(fakeFile, "Tuxedo Plant", "attacker") << endl;
    cout << findFlavorText(monsterFile, "fake monster", "attacker") << endl;
    cout << findFlavorText(monsterFile, "Tuxedo Plant", "destructionSequence") << endl;

    return 0;
}