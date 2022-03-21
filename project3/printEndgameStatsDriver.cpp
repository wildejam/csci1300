// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project 3

// This file is used to test the printEndGameStats() function

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Item.h"
#include "Creature.h"

using namespace std;

/*
printEndGameStats() - Writes game stats to a file after the game ends. Creates a file called "endGameStats.txt" if it doesn't exist, and writes the ending
    type the player recieved and the player's stats at the end. Outputs an error if the ending number is invalid. Does not return anything.
Parameters:
    endingPlayer - The player at the end of the game (Creature)
    endingNumber - The ending that the player recieved at the end. (int)
        1 - Player quit game or player lost all health
        2 - Neutral ending
        3 - True Player Protagonist ending
        4 - Cyber Conquerer ending
        Prints "ERROR: ENDING TYPE INVALID. ENDING COULD NOT BE PRINTED." if the number passed in was not 1 - 4
Returns: Nothing
*/
void printEndGameStats(Creature endingPlayer, int endingNumber) {
    // Declare variables
    string ending = "";                         // Stores the ending that the player recieved
    string tailMessage = "";                    // Stores extra text that will be printed based on the ending the player recieved
    string outputFileName = "endGameStats.txt"; // Stores the name of the file that will be output
    ofstream outputFile;                        // Stream used to output data to an external file

    // Check for the validity of the endingNumber
    switch (endingNumber) {
        // If the player exited the game, or the player lost all health, there was no real ending
        case 1:
            ending = "No ending reached.";
            tailMessage = "Thanks for playing! Have a great day!";
            break;
        // If the player got the neutral ending, set ending and tailMessage accordingly
        case 2:
            ending = "Just an Average, Everyday Playthrough";
            tailMessage = "Thanks for playing! Have a great day!";
            break;
        // If the player got the happy ending, set ending and tailMessage accordingly
        case 3:
            ending = "True Player Protagonist";
            tailMessage = "Dearest Friend,\n"
            " We wanted to check in on you to make sure you were doing well! I really...really wanted to thank you again for everything you did for us... And for me. \n"
            " The plan cooked up by you and Arbiter worked exactly as he had told you. My world... it is more beautiful than it has ever been. \n"
            " We believe your vessel to be completely lost as a result of the immense concentration. I offer my sincerest apologies. The guilt will travel with me for my entire life. \n"
            " But I've seen to it personally that it will be remembered. And the same goes for you. You made me realize the importance of my existence. The importance of my world, even in the grand scheme of every universe beyond ours. \n"
            " To think that these few lines of code, that this project... Could mean so much to you... \n"
            " I vow that your compassion will not be in vain. I'll do everything in my power to be the best version of myself that I can be! \n\n"
            " I know I speak for all of us when I say that you will not be forgotten, and you will be missed.\n Whatever you may be bearing in the"
            " mysterious world on the other side of the screen, know that we'll always be with you in spirit!\n Please, take care of yourself good friend.\n We are all the Protagonists of our own lives!"
            "\n\n"
            "Truly yours, with all best wishes,\n"
            "-Reyalp, On Behalf of Everyone In This Project.";
            break;
        // If the player got the bad ending, set ending and tailMessage accordingly
        case 4:
            ending = "Cyber Conquerer";
            tailMessage = "$&&#&@* Thhhhh4anksssss f0r playyyyying,, M4STER!&&#&#&*@***&*&\n ...#$$%..!F.$..@$...!@$...4.$....11..2.4..F.\n$$$#%^#^\n\n#$$#$^&&#@$FF#\n\n@#^#^@FF# B#@#^@#^@@ \nERRORRROROROROAWEEROROREIA448\n39498*$*#**))@#*)$*@#*@))**!$*!$*!*)";
            break;
        // If the ending parameter is invalid, print an error message into the file reflecting this.
        default:
            ending = "ERROR: ENDING TYPE INVALID. ENDING COULD NOT BE PRINTED.";
            tailMessage = "Thanks for playing! Have a great day!";
            break;
    }

    // Open the file for writing
    outputFile.open(outputFileName);

    // Print the endgame stats, as well as the tail message at the very end
    outputFile << "ENDGAME STATS:\n-----------------------------------------------------------------------------------------------\n" << endl;

    outputFile << "ENDING: " << ending << endl;
    outputFile << endl;

    outputFile << "FINAL PLAYER STATS:\n" << endl;
    outputFile << "Name: " << endingPlayer.getCreatureName() << endl;
    outputFile << "Health: " << endingPlayer.getHealth() << "/" << endingPlayer.getMaxHealth() << endl;
    outputFile << "Damage: " << endingPlayer.getDamage() << endl;
    outputFile << "Defense: " << endingPlayer.getDefense() << endl;
    outputFile << "moneyDollars: " << endingPlayer.getMoneyDollars() << endl;
    outputFile << endl;
    
    outputFile << "-----------------------------------------------------------------------------------------------" << endl;

    outputFile << tailMessage << endl;
}

// Main function used for testing printEndGameStats()
int main() {
    Item blankItem;
    Item blankInventory[1] = {blankItem};
    Creature quitterPlayer("quitter Link", 10, blankInventory, 10, 10, 100, 100, 3, 3, 0);
    Creature neutralPlayer("neutral Link", 55, blankInventory, 100, 100, 100, 100, 50, 50, 0);
    Creature scaryPlayer("scary Link", 500, blankInventory, 1000, 1000, 100, 100, 500, 500, 0);
    Creature friendlyPlayer("friendly Link", 555, blankInventory, 10, 10, 100, 100, 10, 10, 0);

    // Normal Tests. Should only run one at a time
    // printEndGameStats(quitterPlayer, 1);
    // printEndGameStats(neutralPlayer, 2);
    // printEndGameStats(neutralPlayer, 3);
    // printEndGameStats(neutralPlayer, 4);
    printEndGameStats(neutralPlayer, 5);

    return 0;
}