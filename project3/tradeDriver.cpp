// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project #3

// This file is used to test the trade() function

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Item.h"
#include "Creature.h"
#include "Merchant.h"
#include "Party.h"
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

/*
trade() - Function used to simulate trading with a merchant in the game. Takes in the playerParty and the merchant involved, and
    takes in user input for what they wish to do during the trade. Also takes in a file name for flavor text. Returns nothing.
Parameters:
    playerParty - The playerParty that is currently trading. Passed by reference. (Party)
    merchant - The merchant who is currently being traded with. Passed by reference. (Merchant)
    textFileName - The filename of the flavor text file (string)
Returns: Nothing
*/
void trade(Party& playerParty, Merchant& merchant, string textFileName) {
    // Declare variables
    Creature updatedPlayer = playerParty.getPartyMemberAt(0);   // Duplicate player so that changes can be made to the player's inventory and money
    int userInput = 0;                                          // Stores user input
    int userInput2 = 0;                                         // Stores user input
    int dialogueTextCounter = 0;                                // Used to keep track of which dialogue the merchant should say after a certain amount of times.

    // While the user does not wish to leave,
    while (userInput != 3) {
        // Print flavor text. Prompt and get input for what the user wishes to do
        cout << merchant.getMerchantName() << endl;
        cout << findFlavorText(textFileName, merchant.getMerchantName(), "default") << endl;
        cout << "1. Buy \n2. Talk \n3. Leave " << endl;
        cin >> userInput;

        // If the user wishes to buy something, proceed with the buying process
        if (userInput == 1) {

            // If the player's inventory is full, print a message reflecting such and return to the while loop.
            if (updatedPlayer.getCurrentInventorySize() == updatedPlayer.getMaxInventorySize()) {
                cout << "Your inventory is full!" << endl;
            }

            // If the player's inventory is not full, proceed with the buying process
            else {
                // Display a secondary menu. While the user does not wish to exit this new menu,
                while (userInput != 0 && updatedPlayer.getCurrentInventorySize() < updatedPlayer.getMaxInventorySize()) {
                    // Print the merchant's items and the player's money, and get input for which item the player wishes to purchase.
                    cout << endl;
                    cout << "moneyDollars: " << updatedPlayer.getMoneyDollars() << " mD" << endl;
                    cout << "Choose an item to purchase. Input 0 to back out. " << endl;
                    for (int i = 0; i < merchant.getMaxInventorySpace(); i++) {
                        cout << left << setfill(' ') << i + 1 << ". " << setw(30) << merchant.getItemAt(i).getItemName() << setw(5) << merchant.getPriceAt(i) << endl;
                    }
                    cin >> userInput;

                    // If the player chose a valid item,
                    if (userInput > 0 && userInput <= merchant.getMaxInventorySpace() && merchant.getItemAt(userInput - 1).getItemName() != "") {
                        // Print the item name, description, and price. Confirm if the user wishes to purchase this item.
                        cout << endl;
                        cout << merchant.getItemAt(userInput - 1).getItemName() << endl;
                        cout << merchant.getItemAt(userInput - 1).getItemDescription() << endl;
                        cout << "Price: " << merchant.getPriceAt(userInput - 1) << " mD " << endl;
                        cout << "Are you sure you wish to purchase this item? Enter 1 for Yes. Enter 2 for No." << endl;
                        cin >> userInput2;

                        // If the player wished to purchase the item,
                        if (userInput2 == 1) {
                            // If the player doesn't have enough money, print the "not enough money" flavor text and cancel the transaction.
                            if (updatedPlayer.getMoneyDollars() < merchant.getPriceAt(userInput - 1)) {
                                cout << findFlavorText(textFileName, merchant.getMerchantName(), "notenoughmoney") << endl;
                                cout << "Transaction cancelled. " << endl;
                                cin.ignore();
                            }
                            // If the player has enough money, proceed with the transaction
                            else {
                                // Decrease the player's money
                                updatedPlayer.setMoneyDollars(updatedPlayer.getMoneyDollars() - merchant.getPriceAt(userInput - 1));
                                // Place the item in the first available empty slot in the player's inventory
                                for (int i = 0; i < updatedPlayer.getMaxInventorySize(); i++) {
                                    if (updatedPlayer.getInventoryItemAt(i).getItemName() == "") {
                                        updatedPlayer.setInventoryItemAt(i, merchant.getItemAt(userInput - 1));
                                        updatedPlayer.setCurrentInventorySize(updatedPlayer.getCurrentInventorySize() + 1);
                                        break;
                                    }
                                }
                                // Print messages reflecting the results of the transaction
                                cout << "You purchased " << merchant.getItemAt(userInput - 1).getItemName() << "!" << endl;
                                cout << "You have " << updatedPlayer.getMoneyDollars() << " moneyDollars left." << endl;
                                cin.ignore();
                                cin.ignore();
                            }
                        }

                        // If the user decides to not go through with the transaction, print a message reflecting such.
                        else if (userInput2 == 2) {
                            cout << "Transaction cancelled. " << endl;
                            cin.ignore();
                        }

                        // If the user enters invalid input, cancel the transaction.
                        else {
                            cout << "Invalid input. Transaction cancelled. " << endl;
                            cin.clear();
                            cin.ignore();
                        }
                    }

                    // If the user wishes to back out of this secondary menu, back out of the menu by exiting the loop
                    else if (userInput == 0) {
                        cout << endl;
                        break;
                    }
                    
                    // If the user chose an invalid item, print the invalid item flavor text and clear the input.
                    else {
                        cout << findFlavorText(textFileName, merchant.getMerchantName(), "invaliditem");
                        cin.clear();
                        cin.ignore();
                        cin.ignore();
                    }
                }
            }
        }

        // If the user wished to speak with the merchant,
        else if (userInput == 2) {
            // If this is the first time the player has spoken to the merchant, print the first dialogue option
            if (dialogueTextCounter == 0) {
                cout << findFlavorText(textFileName, merchant.getMerchantName(), "dialogue1") << endl;
                cin.ignore();
                cin.ignore();
            }
            // If this is the second time the player has spoken to the merchant, print the second dialogue option.
            else if (dialogueTextCounter == 1) {
                cout << findFlavorText(textFileName, merchant.getMerchantName(), "dialogue2") << endl;
                cin.ignore();
                cin.ignore();
            }
            // In all subsequent times the player talks to the merchant, print the same final dialogue option.
            else {
                cout << findFlavorText(textFileName, merchant.getMerchantName(), "dialoguefinal") << endl;
                cin.ignore();
                cin.ignore();
            }
            // Increment the counter to keep track of the times the player spoke to the merchant.
            dialogueTextCounter++;
        }

        // If the player chose to leave, print the goodbye flavor text.
        else if (userInput == 3) {
            cout << findFlavorText(textFileName, merchant.getMerchantName(), "goodbye") << endl;
            cin.ignore();
            cin.ignore();
        }

        // If the player's input was invalid, print "Invalid Input."
        else {
            cout << "Invalid Input." << endl;
            cin.clear();
            cin.ignore();
        }
    }
    // At the very end, once the player is completely done, update the playerParty with the new, updated player.
    playerParty.setPartyMemberAt(0, updatedPlayer);
}

// Main function used for testing trade()
int main() {
    // Setup
    string flavorTextFile = "merchantFlavorText.txt";

    Item blankItem;
    Item healyPotion("Healy Potion", "heals u", 10, 0, 0);
    Item sword("sword", "hits things", 0, 10, 0);
    Item helmet("helmet", "safety first", 0, 0, 10);
    Item ring("ring", "put it on your finger", 10, 10, 0);
    Item bracelet("bracelet", "put it on your wrist", 10, 0, 10);
    Item store1[5] = {healyPotion, sword, helmet, ring, bracelet};
    Item store2[3] = {healyPotion, ring, bracelet};
    Item store3[2] = {sword, helmet};
    Item store4[1] = {healyPotion};
    int store1Prices[5] = {10, 15, 15, 20, 20};
    int store2Prices[3] = {10, 20, 20};
    int store3Prices[2] = {15, 15};
    int store4Prices[1] = {10};

    Item inventory1[10] = {healyPotion, blankItem, healyPotion, healyPotion, blankItem, blankItem, blankItem, healyPotion, healyPotion, blankItem};
    Creature player("Lunk", 50, inventory1, 10, 10, 10, 10, 10, 10, 5);
    Creature party1[1] = {player};
    Party stonkParty(party1, 1);

    Merchant startyJohn("Starty John", store4, store4Prices, 1);
    Merchant tomYeh("Professor Yeh", store3, store3Prices, 3);
    Merchant darkDealer("The Dark Dealer", store2, store2Prices, 3);
    Merchant drCynth("Dr. Cynth", store1, store1Prices, 5);

    // Test runs
    trade(stonkParty, startyJohn, flavorTextFile);
    trade(stonkParty, tomYeh, flavorTextFile);
    trade(stonkParty, darkDealer, flavorTextFile);
    trade(stonkParty, drCynth, flavorTextFile);

    return 0;
}