// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project #3

// This driver file is used to test the monsterAttacksParty() function

#include <iostream>
#include <random>
#include <fstream>
#include "Item.h"
#include "Creature.h"
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
monsterAttacksParty() - Function used to simulate a monster attacking the party. Takes in the playerParty, number of creatures in the party,
    enemy monster, and a flavor text filename for the monster. Monsters will attack the player every time, but if the player takes damage higher than their health,
    a random ally monster from the party will absorb the damage for the player for that specific attack. Does not return anything. Uses findFlavorText()
Parameters:
    playerParty - The creatures composing the player's party. Passed by reference. (Party)
    creaturesInParty - The amount of creatures stored in the playerParty[] array (int)
    enemy - The enemy creature that the player is fighting. Passed by reference (Creature)
    textFileName - The name of the file containing the flavor text for the monster (string)
Returns: Nothing
*/
void monsterAttacksParty(Party& playerParty, int creaturesInParty, Creature& enemy, string textFileName) {
    // Assign player and enemy stats to variabes for readability
    int playerHealth = playerParty.getPartyMemberAt(0).getHealth();
    int playerDefense = playerParty.getPartyMemberAt(0).getDefense();
    int enemyDamage = enemy.getDamage();
    int damageToPlayer = (enemyDamage * 1.0) * ((100 * 1.0) / ((100 + playerDefense) * 1.0));

    // Print the flavor text for the monster attacking
    cout << findFlavorText(textFileName, enemy.getCreatureName(), "attacker") << endl;
    cin.ignore();

    // If the attack would have KO'd the player, have a random ally tank the hit for the player.
    if (damageToPlayer >= playerHealth && creaturesInParty > 1) {
        int randomPartyMember = (rand() % (creaturesInParty - 1)) + 1;                    // Choose a random party index
        Creature updatedAlly = playerParty.getPartyMemberAt(randomPartyMember);     // Duplicate the creature at that index, to replace the old one later
        Creature updatedPlayer = playerParty.getPartyMemberAt(0);                   // Duplicate the player, to replace the old one later
        

        // If the randomly chosen ally has 0 health or less, a new ally will be chosen when the function enters this loop.
        int i = 0;  // Variable tracks the number of occurences of this loop
        while (updatedAlly.getHealth() <= 0) {
            // Increment the index to search for a party member
            randomPartyMember++;
            // If the loop reaches a point where it has checked every party member and still no alive allies were found,
            if (i == creaturesInParty - 1) {
                // The player must have taken enough damage such that their health is 0, so set it to 0...
                updatedPlayer.setHealth(0);
                // ...Replace the player object in the party with the duplicated, updated one...
                playerParty.setPartyMemberAt(0, updatedPlayer);
                // ...And print a message describing the events. Exit the function afterward.
                cout << updatedPlayer.getCreatureName() << " takes " << damageToPlayer << " damage!" << endl;
                cin.ignore();
                cout << updatedPlayer.getCreatureName() << " now has " << updatedPlayer.getHealth() << "/" << updatedPlayer.getMaxHealth() << " HP." << endl;
                cin.ignore();
                return;
            }
            // If the index reaches the end of the party, return to the beginning of the party selection and continue searching
            if (randomPartyMember - 1 == creaturesInParty - 1) {
                randomPartyMember = 1;
            }
            // Set the newly found party member to be the new updatedAlly
            updatedAlly = playerParty.getPartyMemberAt(randomPartyMember);
            // Increment i to keep track of how many party members have been searched.
            i++;
        }

        // If a party member with more than 0 health was found, proceed with applying the damage to the creature.
        // Assign battle values to variables for readability
        int allyHealth = updatedAlly.getHealth();
        int allyDefense = updatedAlly.getDefense();
        int damageToAlly = (enemyDamage * 1.0) * ((100 * 1.0) / ((100 + allyDefense) * 1.0));

        // Apply the damage from the enemy to the ally. If it results in the ally having a health less than 0, set their health to 0.
        updatedAlly.setHealth(allyHealth - damageToAlly);
        if (updatedAlly.getHealth() < 0) {
            updatedAlly.setHealth(0);
        }

        // Then replace the creature in the party array with the updated creature
        playerParty.setPartyMemberAt(randomPartyMember, updatedAlly);

        // And print messages describing what occurred.
        cout << updatedAlly.getCreatureName() << " takes the blow for you!" << endl;
        cin.ignore();
        cout << updatedAlly.getCreatureName() << " takes " << damageToAlly << " damage!" << endl;
        cin.ignore();
        cout << updatedAlly.getCreatureName() << " now has " << updatedAlly.getHealth() << "/" << updatedAlly.getMaxHealth() << " HP." << endl;
        cin.ignore();
    }

    // If the player doesn't have any allies, or if the damage would not have been sufficient to knock out the player, apply damage to the player normally.
    else {
        // Duplicate the player
        Creature updatedPlayer = playerParty.getPartyMemberAt(0);

        // Apply the damage to the player. If the player's health is less than 0, set their health to 0.
        updatedPlayer.setHealth(playerHealth - damageToPlayer);
        if (updatedPlayer.getHealth() < 0) {
            updatedPlayer.setHealth(0);
        }

        // Replace the player object in the party with the new, updated player object
        playerParty.setPartyMemberAt(0, updatedPlayer);

        // Print messages describing what happened.
        cout << updatedPlayer.getCreatureName() << " takes " << damageToPlayer << " damage!" << endl;
        cin.ignore();
        cout << updatedPlayer.getCreatureName() << " now has " << updatedPlayer.getHealth() << "/" << updatedPlayer.getMaxHealth() << " HP." << endl;
        cin.ignore();
    }

}               

// Main function used for testing monsterAttacksParty()
int main() {
    srand(time(NULL));
    string flavorTextFile = "monsterFlavorText.txt";

    // Setup (Party, enemy, filename)
    Item blankItem;
    Item blankInventory[3] = {blankItem, blankItem, blankItem};
    Creature human("Lank", 10, blankInventory, 25, 20, 10, 10, 5, 5, 3);
    Creature ally1("ally1", 0, blankInventory, 20, 20, 20, 20, 5, 5, 0);
    Creature ally2("ally2", 0, blankInventory, 30, 30, 30, 30, 5, 5, 0);
    Creature deadAlly("ally3", 0, blankInventory, 10, 0, 10, 10, 10, 10, 0);
    Creature enemyMonster("Rabid Docat", 10, blankInventory, 20, 20, 30, 30, 20, 5, 0);
    Creature powerfulEnemyMonster("General Arbiter", 10, blankInventory, 100, 100, 100, 100, 500, 300, 0);
    
    Creature playerParty[3] = {human, ally1, ally2};
    Creature playerParty2[1] = {human};
    Creature playerParty3[4] = {human, deadAlly, deadAlly, deadAlly};
    Party funGang(playerParty, 3);
    Party lameGang(playerParty2, 1);
    Party sadGang(playerParty3, 4);

    
    // Normal case: other allies in party, attack doesn't kill
    monsterAttacksParty(funGang, funGang.getCurrentPartySize(), enemyMonster, flavorTextFile);
    funGang.printAllPartyMembers();

    // Normal case: Other, alive monsters in player's party, attack kills
    monsterAttacksParty(funGang, funGang.getCurrentPartySize(), powerfulEnemyMonster, flavorTextFile);
    funGang.printAllPartyMembers();

    // Normal case: No other monsters in player's party, attack kills
    monsterAttacksParty(lameGang, lameGang.getCurrentPartySize(), powerfulEnemyMonster, flavorTextFile);
    lameGang.printAllPartyMembers();

    // Normal case: Other monsters in party, but all have 0 hp, attack kills
    monsterAttacksParty(sadGang, sadGang.getCurrentPartySize(), powerfulEnemyMonster, flavorTextFile);
    sadGang.printAllPartyMembers();

    return 0;
}