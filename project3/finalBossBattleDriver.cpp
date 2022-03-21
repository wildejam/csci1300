// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project #3

// This file is used to test the finalBossBattle() function

#include <iostream>
#include <iomanip>
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
useItem() - Function used to simulate using an item on a creature in the player's party. Takes in the player party, and asks the user for which item they wish to use on 
    which creature. Returns 0 if procedure was successful. Returns -1 if player wished to exit.
Parameters:
    playerParty - The creatures composing the player's party. Passed by reference. (Party)
    creaturesInParty - The amount of creatures stored in the playerParty[] array (int)
Returns: 
    0 if the procedure for applying an item to a creature was successful
    -1 if the player wished to exit the function early.
*/
int useItem(Party& playerParty, int creaturesInParty) {
    // Declare variables
    int userBattleInput = 0;    // Variable used to store user input
    int userBattleInput2 = 0;   // Variable used to store user input
    bool inputCheck1 = false;   // Bool used to check input, and make the menu loops function properly
    bool inputCheck2 = false;   // Bool used to check input, and make the menu loops function properly
    Item blankItem;             // Blank item used to replace item that is used by the player
    Creature updatedInventoryCreature = playerParty.getPartyMemberAt(0);    // New creature used to replace player in the party when inventory is updated.
    int maxInventorySize = updatedInventoryCreature.getMaxInventorySize();  // Set a variable to store the current amount of items in the player's inventory

            // While the input is not valid
            do {
                cout << endl;
                // Prompt and get input for which item the player wishes to use. Print a list of items the player currently has each time.
                cout << "Choose an item to use. Input 0 to back out:" << endl;
                for (int i = 0; i < maxInventorySize; i++) {
                    cout << left << setfill(' ') << i + 1 << "." << updatedInventoryCreature.getInventoryItemAt(i).getItemName() << endl;
                }
                cin >> userBattleInput;

                // If the input was 0, exit the function without modifying the party.
                if (userBattleInput == 0) {
                    return -1;
                }

                // If the input was greater than the size of the inventory, less than 1, or suggested an item that does not exist, print an error message.
                if (userBattleInput > maxInventorySize || userBattleInput < 1 || updatedInventoryCreature.getInventoryItemAt(userBattleInput - 1).getItemName() == "") {
                    cout << "That item doesn't exist!" << endl;
                }

                // If the input was valid, and suggested an item that does indeed exist,
                else if (userBattleInput <= maxInventorySize && userBattleInput > 0) {
                    // Set the first inputCheck flag to true, so that the menu will be exited after this operation
                    inputCheck1 = true;
                    // Prompt and get input once more for which creature in the party the player wishes to use their chosen item on, while the input is invalid
                    do {
                        cout << endl;
                        cout << "Who would you like to use the item on? Input 0 to back out." << endl;
                        for (int j = 0; j < playerParty.getCurrentPartySize(); j++) {
                            cout << left << setfill(' ') << j + 1 << ". " << playerParty.getPartyMemberAt(j).getCreatureName() << endl;
                        }
                        cin >> userBattleInput2;

                        // If the player chose to back out, exit the function without modifying the party.
                        if (userBattleInput2 == 0) {
                            return -1;
                        }

                        // If the player chose a party member that doesn't exist, print an error message
                        if (userBattleInput2 > playerParty.getCurrentPartySize() || userBattleInput2 < 1) {
                            cout << "That party member doesn't exist!" << endl;
                        }

                        // If the player chose a valid party member, proceed with applying the effects of the item to the specific creature
                        // This must be done by duplicating the creature, updating the stats of new creature after the item effect, and then replacing the creature in the party
                        // with the new one. We also need to remove the item from the player's inventory with a similar procedure.
                        else if (userBattleInput2 <= playerParty.getCurrentPartySize() && userBattleInput2 > 0) {
                            // Set the second input check flag to true, so that the menu will be exited after this operation
                            inputCheck2 = true;
                            // Create a new creature that is identical to the one currently in the party
                            Creature updatedPartyCreature = playerParty.getPartyMemberAt(userBattleInput2 - 1);

                            // Assign variables to item stats and creature initial stats, to make calling setter functions more readable
                            string itemTargetName = updatedPartyCreature.getCreatureName();
                            int itemTargetCurrentHealth = updatedPartyCreature.getHealth();
                            int itemTargetCurrentDmg = updatedPartyCreature.getDamage();
                            int itemTargetCurrentDefense = updatedPartyCreature.getDefense();
                            int itemHealthImpact = updatedInventoryCreature.getInventoryItemAt(userBattleInput - 1).getHpImpact();
                            int itemDmgImpact = updatedInventoryCreature.getInventoryItemAt(userBattleInput - 1).getDmgImpact();
                            int itemDefenseImpact = updatedInventoryCreature.getInventoryItemAt(userBattleInput - 1).getDefImpact();

                            // Apply the effects of the item to the creature's stats, and remove the item from the player's inventory, replacing it with a blank item.
                            updatedPartyCreature.setHealth(itemTargetCurrentHealth + itemHealthImpact);
                            updatedPartyCreature.setDamage(itemTargetCurrentDmg + itemDmgImpact);
                            updatedPartyCreature.setDefense(itemTargetCurrentDefense + itemDefenseImpact);
                            // If the creature that used the item is the same as the creature that recieved the effects, apply the effects to the inventory creature as well
                            if (userBattleInput2 - 1 == 0) {
                                updatedInventoryCreature.setHealth(itemTargetCurrentHealth + itemHealthImpact);
                                updatedInventoryCreature.setDamage(itemTargetCurrentDmg + itemDmgImpact);
                                updatedInventoryCreature.setDefense(itemTargetCurrentDefense + itemDefenseImpact);
                            }
                            updatedInventoryCreature.setInventoryItemAt(userBattleInput - 1, blankItem);
                            updatedInventoryCreature.setCurrentInventorySize(updatedInventoryCreature.getCurrentInventorySize() - 1);


                            // If the item caused the creature to have more health than their max health, set their health to be their max health.
                            if (updatedPartyCreature.getHealth() > updatedPartyCreature.getMaxHealth()) {
                                updatedPartyCreature.setHealth(updatedPartyCreature.getMaxHealth());
                            }
                            if (updatedInventoryCreature.getHealth() > updatedInventoryCreature.getMaxHealth()) {
                                updatedInventoryCreature.setHealth(updatedInventoryCreature.getMaxHealth());
                            }

                            // Then, replace the Creature instances within the party with the updated ones.
                            // This allows inventory and stat changes made to the party to be carried through.
                            playerParty.setPartyMemberAt(0, updatedInventoryCreature);
                            // If the creature recieving the item was not the same as one using the item, also update that creature with the new health.
                            if (!(userBattleInput2 - 1 == 0)) {
                                playerParty.setPartyMemberAt(userBattleInput2 - 1, updatedPartyCreature);
                            }
                            
                            // Print the effects of the item to the console.
                            cout << itemTargetName << " gained " << itemHealthImpact << " HP!" << endl;
                            cout << itemTargetName << " gained " << itemDmgImpact << " Damage!" << endl;
                            cout << itemTargetName << " gained " << itemDefenseImpact << " Defense!" << endl;

                            return 0;
                        }
                        // If the player chose an invalid creature, print a message reflecting this
                        else {
                            cout << "Invalid input!" << endl;
                        }
                    }
                    while (!(userBattleInput2 > 0 && userBattleInput2 <= playerParty.getCurrentPartySize() && inputCheck2));
                }
                // If the player chose an invalid item, print a message reflecting this.
                else {
                    cout << "Invalid input!" << endl;
                }
            }
            while (!(userBattleInput > 0 && userBattleInput <= maxInventorySize && inputCheck1));

    // If the function reaches this point, it's safe to assume the item effects were not applied. Return -1
    return -1;
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


/*
battle() - Function used to simulate a battle in the game. Takes in the various players within the battle and modifies their stats based
    on player input and the outcome of the battle. Does not return anything. Uses findFlavorText(), monsterAttacksParty(), and useItem() functions.
Parameters:
    playerParty - The creatures composing the player's party. Passed by reference. (Party)
    creaturesInParty - The amount of creatures stored in the playerParty[] array (int)
    enemy - The enemy creature that the player is fighting. Passed by reference (Creature)
    textFileName - The name of the file containing the flavor text for the monster (string)
Returns: Nothing
*/
void battle(Party& playerParty, int creaturesInParty, Creature& enemy, string textFileName) {
    // Declare variables
    int userBattleInput = 0;    // Variable used to store user input

    // When the battle begins, print the beginning battle flavor text for the monster being fought
    cout << findFlavorText(textFileName, enemy.getCreatureName(), "beginningbattle") << endl;
    cout << endl;
    // MAIN BATTLE LOOP; WALKS THROUGH UNTIL EITHER PLAYER LOSES ALL HP OR ENEMY MONSTER LOSES ALL HP, OR MONSTER LOSES ALL PSYCHE
    while (playerParty.getPartyMemberAt(0).getHealth() > 0 && enemy.getHealth() > 0 && enemy.getPsyche() > 0) {
        userBattleInput = 0;    // Reset battle input to be 0 every time the loop restarts

        // Print idle flavor text, then prompt and get input for what the player wishes to do
        cout << findFlavorText(textFileName, enemy.getCreatureName(), "idle") << endl;
        cout << "What would you like to do? Choose a number: " << endl;
        cout << "1. Attack \n2. Befriend \n3. Use Item \n4. Check Party \n5. Check Monster" << endl;
        cin >> userBattleInput;
        cout << endl;

        // If the player wishes to attack the monster,
        if (userBattleInput == 1) {
            // Assign variables to relevant stats for readability, and print flavor text for the attack.
            int initialEnemyHealth = enemy.getHealth();
            int playerDamage = playerParty.getPartyMemberAt(0).getDamage();
            int playerDamageToMonster = (playerDamage * 1.0) * ((100 * 1.0) / ((100 + enemy.getDefense()) * 1.0));
            cout << findFlavorText(textFileName, enemy.getCreatureName(), "attacked") << endl;
            cin.ignore();

            // Update the health of the enemy. If the health dropped below 0, set the monster's health to 0
            enemy.setHealth(enemy.getHealth() - playerDamageToMonster);
            if (enemy.getHealth() < 0) {
                enemy.setHealth(0);
            }

            // Print results of engagement
            cout << enemy.getCreatureName() << " took " << playerDamageToMonster << " damage!" << endl;
            cin.ignore();
            cout << enemy.getCreatureName() << " now has " << enemy.getHealth() << "/" << enemy.getMaxHealth() << " HP!" << endl;
            cin.ignore();
            cout << endl;
            
            // If this attack caused the monster to reach 0 HP, break from the loop and go straight to ending battle conditions
            if (enemy.getHealth() <= 0) {
                break;
            }

            // If the monster still has HP, have the monster take a turn by attacking the party.
            monsterAttacksParty(playerParty, playerParty.getCurrentPartySize(), enemy, textFileName);
        }

        // If the player chose to befriend the monster
        else if (userBattleInput == 2) {
            // Assign enemy's psyche to a varable for readability, and print flavor text describing how the befriending went
            int initialEnemyPsyche = enemy.getPsyche();
            cout << findFlavorText(textFileName, enemy.getCreatureName(), "befriended") << endl;
            cin.ignore();

            // Update the enemy's psyche. If the psyche dropped to below 0, update the psyche of the monster to be 0.
            enemy.setPsyche(enemy.getPsyche() - 1);
            if (enemy.getPsyche() < 0) {
                enemy.setPsyche(0);
            }

            // Print results of the engagement
            cout << enemy.getCreatureName() << " took 1 psyche damage!" << endl;
            cin.ignore();
            cout << enemy.getCreatureName() << " now has " << enemy.getPsyche() << "/" << enemy.getMaxPsyche() << " Psyche!" << endl;
            cin.ignore();

            // If the engagement resulted in the monster having 0 psyche, break from the loop and go straight to the ending battle conditions
            if (enemy.getPsyche() <= 0) {
                break;
            }

            // If the monster is still above 0 psyche, have the monster attack the player's party
            monsterAttacksParty(playerParty, playerParty.getCurrentPartySize(), enemy, textFileName);
        }

        // If the player chose to use an item,
        else if (userBattleInput == 3) {
            cout << endl;
            // Walk the player through the Use Item sequence. If that function returned a 0, the item application was successful, so walk through a monster attack turn.
            // If the application was not successful, the monster does not get to have its turn yet, so this statement will be skipped over.
            if (useItem(playerParty, creaturesInParty) == 0) {
                cin.ignore();
                monsterAttacksParty(playerParty, playerParty.getCurrentPartySize(), enemy, textFileName);
            }

        }

        // If the player chose to display the party stats, display them
        else if (userBattleInput == 4) {
            cout << endl;
            playerParty.printAllPartyMembers();
            cout << endl;
            cout << endl;
        }

        // If the player chose to display the enemy stats, display them
        else if (userBattleInput == 5) {
            cout << endl;
            enemy.printStats();
            cout << endl;
            cout << endl;
        }

        // If the player's input was invalid, print "Invalid Input!" and clear the input from cin
        else {
            cout << "Invalid Input!" << endl;
            cin.clear();
            cin.ignore();
        }
    }

    // ONCE THE BATTLE IS OVER, CHECK FOR WHY THE BATTLE ENDED TO DETERMINE AFTERMATH
    // If the battle ended as a result of the player losing all health, print a message reflecting this, and exit the function
    if (playerParty.getPartyMemberAt(0).getHealth() <= 0) {
        cout << "You have fallen in battle!" << endl;
    }

    // If the battle ended as a result of the monster losing all health, make the player stronger
    else if (enemy.getHealth() <= 0) {
        // Duplicate the player
        Creature updatedPlayer = playerParty.getPartyMemberAt(0);

        // Improve the player's stats based on the monster that was just fought, and place monster's money into player's money.
        updatedPlayer.setMoneyDollars(updatedPlayer.getMoneyDollars() + enemy.getMoneyDollars());
        updatedPlayer.setMaxHealth(updatedPlayer.getMaxHealth() + enemy.getMaxHealth());
        updatedPlayer.setDamage(updatedPlayer.getDamage() + enemy.getDamage());
        updatedPlayer.setDefense(updatedPlayer.getDefense() + enemy.getDefense());
        // Replace the player currently in the party with the updated player Creature
        playerParty.setPartyMemberAt(0, updatedPlayer);

        // Print text reflecting the outcome, then exit the function
        cout << enemy.getCreatureName() << " was slain." << endl;
        cin.ignore();
        cout << "You gained " << enemy.getMoneyDollars() << " moneyDollars." << endl;
        cout << "You gained " << enemy.getMaxHealth() << " max Health points." << endl;
        cout << "You gained " << enemy.getDamage() << " more Damage." << endl;
        cout << "You gained " << enemy.getDefense() << " more Defense." << endl;
        cin.ignore();
    }

    // If the battle ended as a result of the monster losing all psyche, add the monster to the player's party, and transfer money from monster to player
    else if (enemy.getPsyche() <= 0) {
        // Duplicate the player, and store the initial moneyDollars the monster had
        Creature updatedPlayer = playerParty.getPartyMemberAt(0);
        int initialMonsterMoney = enemy.getMoneyDollars();
        // Transfer money from monster to player
        updatedPlayer.setMoneyDollars(updatedPlayer.getMoneyDollars() + enemy.getMoneyDollars());
        enemy.setMoneyDollars(0);

        // Replace the player in the party with the new, updated player
        playerParty.setPartyMemberAt(0, updatedPlayer);

        // If the party is full (which it shouldn't be, as party size shouldn't be exceeded in the final game), print a message reflecting this and exit function.
        if (creaturesInParty >= playerParty.getMaxPartyMembers()) {
            cout << "ERROR: CANNOT ADD NEW PARTY MEMBER; PARTY IS FULL." << endl;
            return;
        }
        // If party wasn't full, add the enemy monster to the player's party and increment the party size.
        playerParty.setPartyMemberAt(creaturesInParty, enemy);
        playerParty.setCurrentPartySize(creaturesInParty + 1);

        // Print text reflecting the outcome, then exit the function
        cout << "You gained " << initialMonsterMoney << " moneyDollars! " << endl;
        cout << enemy.getCreatureName() << " is now a member of your party!" << endl;
        cin.ignore();
    }

    // If the battle somehow ended without the player or monster losing all health/psyche, print an error message. For debugging purposes.
    else {
        cout << "ERROR: BATTLE ENDED IMPROPERLY; NO BATTLE RESULTS COULD BE DISPLAYED." << endl;
    }
}


/*
finalBossBattle() - Function used to simulate the final boss battle in the game. Takes in the playerParty, and takes in the boss.
    Modifies stats based on player actions. Is similar but distinct from the battle() function, and has specific narrative sequences. Does not return anything. Uses battle().
Parameters:
    playerParty - The array of creatures composing the player's party. Passed by reference. (Party)
    creaturesInParty - The amount of creatures stored in the playerParty[] array (int)
    bossbossEnemy - The bossEnemy boss that the player is fighting. Passed by reference (Creature)
    textFileName - The name of the file containing the flavor text for the final boss (string)
Returns: Nothing
*/
void finalBossBattle(Party& playerParty, int creaturesInParty, Creature& bossEnemy, string textFileName) {
    // Declare variables
    int userBattleInput = 0;    // Variable used to store user input

    // If the player has not befriended all monsters, but has befriended some, walk through a normal final boss battle.
    // NOTE: If this final battle is reached, it is impossible to befriend the final boss.
    if (playerParty.getCurrentPartySize() > 1 && playerParty.getCurrentPartySize() < 10) {
        battle(playerParty, creaturesInParty, bossEnemy, textFileName);
    }

    // If the player befriended all monsters, or befriended none, walk through a special, custom battle.
    else if (playerParty.getCurrentPartySize() == 1 || playerParty.getCurrentPartySize() == 10) {
        
        // If the player befriended all monsters, The plot is that the monsters were absorbed but the merchants joined the player
        // Update the party to reflect this change, and also make the boss impossibly powerful.
        if (playerParty.getCurrentPartySize() == 10) {
            Item blankItem;
            Item blankInventory[1] = {blankItem};
            Creature newPlayer = playerParty.getPartyMemberAt(0);
            Creature startyJohn("Starty John", 25, blankInventory, 20, 20, 50, 50, 25, 15, 0);
            Creature profYeh("Professor Yeh", 55, blankInventory, 30, 30, 100, 100, 30, 20, 0);
            Creature darkDealer("The Dark Dealer", 275, blankInventory, 55, 55, 100, 100, 55, 50, 0);
            Creature drCynth("Dr. Cynth", 150, blankInventory, 40, 40, 250, 250, 45, 40, 0);
            Creature opBoss("$$R3Y4LP*TH3*D3FEND3R#$", 99999, blankInventory, 999999, 999999, 999, 999, 99999, 99999, 0);
            Creature newParty[5] = {newPlayer, startyJohn, profYeh, darkDealer, drCynth};
            Party updatedParty(newParty, 5);

            playerParty = updatedParty;
            bossEnemy = opBoss;
        }

        // If the player befriended no monsters, set the boss to be a special, more powerful version
        else if (playerParty.getCurrentPartySize() == 1) {
            Item blankItem;
            Item blankInventory[1] = {blankItem};
            Creature powerfulBoss("$$R3Y4LP*TH3*D3FEND3R#$", 99999, blankInventory, 15000, 15000, 999, 999, 1500, 205, 0);

            bossEnemy = powerfulBoss;
        }


        // When the battle begins, print the beginning battle flavor text for the monster being fought
        cout << findFlavorText(textFileName, bossEnemy.getCreatureName(), "beginningbattle") << endl;
        cout << endl;
        // MAIN BATTLE LOOP; WALKS THROUGH UNTIL EITHER PLAYER LOSES ALL HP OR bossEnemy MONSTER LOSES ALL HP
        while (playerParty.getPartyMemberAt(0).getHealth() > 0 && bossEnemy.getHealth() > 0) {
            userBattleInput = 0;    // Reset battle input to be 0 every time the loop restarts

            // Print idle flavor text, then prompt and get input for what the player wishes to do. Text is different from that of battle() function.
            cout << findFlavorText(textFileName, bossEnemy.getCreatureName(), "idle") << endl;
            cout << "What would you like to do? Choose a number: " << endl;
            cout << "1. ##$A++ack** \n";
            // If the player befriended at least one monster, display the befriend text.
            if (playerParty.getCurrentPartySize() > 1) {
                cout << "2. BEFRIEND \n";
            }
            // If not, make the befriend text inaccessible.
            else {
                cout << "2. ErrOR:::::COULD NOT RETRIIEIVE COMMMANDDD###* \n"; 
            }
            cout << "3. ***Us3 Item \n4. Check $%&***F00LS***& \n5. #*#*F1GHT ME*#*#@" << endl;
            cin >> userBattleInput;
            cout << endl;

            // If the player wishes to attack the monster,
            if (userBattleInput == 1) {
                // Assign variables to relevant stats for readability, and print flavor text for the attack.
                int initialbossEnemyHealth = bossEnemy.getHealth();
                int playerDamage = playerParty.getPartyMemberAt(0).getDamage();
                int playerDamageToMonster = (playerDamage * 1.0) * ((100 * 1.0) / ((100 + bossEnemy.getDefense()) * 1.0));
                cout << findFlavorText(textFileName, bossEnemy.getCreatureName(), "attacked") << endl;
                cin.ignore();

                // Update the health of the bossEnemy. If the health dropped below 0, set the monster's health to 0
                bossEnemy.setHealth(bossEnemy.getHealth() - playerDamageToMonster);
                if (bossEnemy.getHealth() < 0) {
                    bossEnemy.setHealth(0);
                }

                // Print results of engagement
                cout << "2341!@$** " << bossEnemy.getCreatureName() << " t00k " << playerDamageToMonster << " d4mage!##@##$" << endl;
                cin.ignore();
                cout << bossEnemy.getCreatureName() << " currently p0$$ESSE$ " << bossEnemy.getHealth() << "///////////" << bossEnemy.getMaxHealth() << " HPointerS!!#$#!" << endl;
                cin.ignore();
                cout << endl;
                
                // If this attack caused the monster to reach 0 HP, break from the loop and go straight to ending battle conditions
                if (bossEnemy.getHealth() <= 0) {
                    break;
                }

                // If the monster still has HP, have the monster take a turn by attacking the party.
                monsterAttacksParty(playerParty, playerParty.getCurrentPartySize(), bossEnemy, textFileName);
            }

            // If the player chose to befriend the monster, and they have befriended at least one monster,
            else if (userBattleInput == 2 && playerParty.getCurrentPartySize() > 1) {
                // Assign bossEnemy's psyche to a varable for readability, and print flavor text describing how the befriending went
                int initialbossEnemyPsyche = bossEnemy.getPsyche();
                cout << findFlavorText(textFileName, bossEnemy.getCreatureName(), "befriended") << endl;
                cin.ignore();

                // Update the bossEnemy's psyche. If the psyche dropped to below 0, update the psyche of the monster to be 0.
                bossEnemy.setPsyche(bossEnemy.getPsyche() - 1);
                if (bossEnemy.getPsyche() < 0) {
                    bossEnemy.setPsyche(0);
                }

                // Print results of the engagement
                cout << bossEnemy.getCreatureName() << " took 1 psych0 d4mmmage!!@##" << endl;
                cin.ignore();
                cout << bossEnemy.getCreatureName() << " n0w has$$ " << bossEnemy.getPsyche() << "/../(**" << bossEnemy.getMaxPsyche() << " Psych@#$$e!" << endl;
                cin.ignore();

                // If the engagement resulted in the monster having 0 psyche, break from the loop and go straight to the ending battle conditions
                // NOTE: This should be impossible at this point.
                if (bossEnemy.getPsyche() <= 0) {
                    break;
                }

                // If the monster is still above 0 psyche, have the monster attack the player's party
                monsterAttacksParty(playerParty, playerParty.getCurrentPartySize(), bossEnemy, textFileName);
            }

            // If the player chose to befriend the boss but they befriended no other monsters (their party is empty), Print a special message and have the boss attack the player.
            else if (userBattleInput == 2 && playerParty.getCurrentPartySize() <= 1) {
                cout << "\"***)()#F00L. IT'S T00 L4TE F0R THAT NOW. Y0UR PETTY TR1CKS WON'T WORK ON ME.***#@#*@)\"" << endl;
                monsterAttacksParty(playerParty, playerParty.getCurrentPartySize(), bossEnemy, textFileName);
            }

            // If the player chose to use an item,
            else if (userBattleInput == 3) {
                cout << endl;
                // Walk the player through the Use Item sequence. If that function returned a 0, the item application was successful, so walk through a monster attack turn.
                // If the application was not successful, the monster does not get to have its turn yet, so this statement will be skipped over.
                cout << "^^$##H4H4AA. U$ING ITEM$ AR3 WE? LUCKy f0R Y0u I h4VEN'T TOUCH3D THAT P4RT OF THE COD3 YET. treasure it while you can. :) ^$$" << endl;
                if (useItem(playerParty, creaturesInParty) == 0) {
                    cin.ignore();
                    monsterAttacksParty(playerParty, playerParty.getCurrentPartySize(), bossEnemy, textFileName);
                }

            }

            // If the player chose to display the party stats, display them
            else if (userBattleInput == 4) {
                cout << "%&$$&**WONDERING WH3RE Y0UR FR1ENDS ARE?#*** HAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHA!!!*#*@#**)" << endl;
                cout << endl;
                playerParty.printAllPartyMembers();
                cout << endl;
                cout << endl;
            }

            // If the player chose to display the bossEnemy stats, display them
            else if (userBattleInput == 5) {
                cout << "**%*$**YOU CANNOT D3F3AT ME FR1END. I 0WN TH1S PL4CE!" << endl;
                cout << endl;
                bossEnemy.printStats();
                cout << endl;
                cout << endl;
            }

            // If the player's input was invalid, print "Invalid Input!" and clear the input from cin. Also have the boss attack the player.
            else {
                cout << "*#*$*F00L! Y0U SHOULD KN0W B3TTER TH4N TO G1VE INV4LID INPUT!**!*) HAHAHAHAHAHAHAHAHAH!" << endl;
                cin.clear();
                cin.ignore();
                monsterAttacksParty(playerParty, playerParty.getCurrentPartySize(), bossEnemy, textFileName);
            }
        }

        // Once the battle ends, walk through specific sequences based on what happened.
        // If the player had befriended no monsters and the player lost all health, exit the function.
        if (playerParty.getPartyMemberAt(0).getHealth() <= 0 && playerParty.getCurrentPartySize() <= 1) {
            cout << "F00L." << endl;
            cin.ignore();
            return;
        }

        // If the player had befriended no monsters, but won the battle by defeating the boss (which should be possible), exit the function
        else if (bossEnemy.getHealth() <= 0 && playerParty.getCurrentPartySize() <= 1) {
            cout << "IMP0$$IBLE!" << endl;
            cin.ignore();
            return;
        }

        // If the player lost the battle, but befriended all monsters, walk through another sequence. This situation is inevitable if the player befriended all monsters.
        // In other words, if the player befriended all monsters, they are supposed to lose this first part of the battle.
        else if (playerParty.getPartyMemberAt(0).getHealth() <= 0 && playerParty.getCurrentPartySize() > 1) {
            // Create an OP version of the player, which will replace the player in the party later.
            Item blankItem;
            Item blankInventory[1] = {blankItem};
            Creature trueProtagonist("YOU, THE PROTAGONIST!", 0, blankInventory, 999999, 999999, 999, 999, 0, 0, 0);

            // Walk through a narrative sequence
            cout << endl;
            cin.ignore();
            cout << "A$ y0U^^# Fall in b4ttle8#*#$%^,, th3 c0d3$* crashes *#*$ down around y0U$$#$#." << endl;
            cin.ignore();
            cout << "\"TH1S W0RLD I$ M1NE. yOU $$CANN0T TAKE THIS AWAY FROM ME**#$\"" << endl;
            cin.ignore();
            cout << "NOW." << endl;
            cin.ignore();
            cout << "D1E." << endl;
            cin.ignore();
            cin.ignore();
            cin.ignore();
            cin.ignore();
            cin.ignore();
            cout << "IMP0SSIBLE..." << endl;
            cin.ignore();
            cout << "You notice that the world has temporarily stabilized. No errors. No issues. No chaos." << endl;
            cin.ignore();
            cout << "And suddenly, you sense a rumbling from Reyalp." << endl;
            cin.ignore();
            cout << "\"THERE'S NO WAY! THESE ARE MY CREATIONS! HOW COULD THIS BE?\"" << endl;
            cin.ignore();
            cout << "Before you get a chance to react, a pure white energy radiates from Emperor Reyalp's chest!" << endl;
            cin.ignore();
            cout << "This mysterious energy directs itself towards you. It begins piercing your chest!" << endl;
            cin.ignore();
            cout << "You suddenly realize an overwhelming familiarity as the pool of energy floods your soul." << endl;
            cin.ignore();
            cout << "You know what this is..." << endl;
            cin.ignore();
            cout << "They want nothing but to help you persevere. They are there with you to the end. They always will be." << endl;
            cin.ignore();
            cout << "Edge Guardian.";
            cin.ignore();
            cout << "Rabid Docat.";
            cin.ignore();
            cout << "Mad Wizard.";
            cin.ignore();
            cout << "Angry Gumball Machine.";
            cin.ignore();
            cout << "Tuxedo Plant.";
            cin.ignore();
            cout << "Ralphie.";
            cin.ignore();
            cout << "Detective Gumshoe.";
            cin.ignore();
            cout << "The Biggest Emu.";
            cin.ignore();
            cout << "And even General Arbiter." << endl;
            cin.ignore();
            cout << "Everyone is here." << endl;
            cin.ignore();
            cout << "The pooling mass of raw energy empowers you to a level you have never felt before. You have become the player. The player is you." << endl;
            cin.ignore();
            cout << "Now is the time to act like it." << endl;
            cin.ignore();
            cout << "You look over to Emperor Reyalp." << endl;
            cin.ignore();
            cout << "\"YOU THINK THIS CAN STOP ME? I'LL CUT YOU DOWN!\"" << endl;
            cin.ignore();

            // Replace the player in the party with the TRUE PROTAGONIST, Overpowered player, and change Reyalp's name.
            playerParty.setPartyMemberAt(0, trueProtagonist);
            bossEnemy.setCreatureName("Reyalp");

            // THIS IS A SECOND BOSS BATTLE, BUT ONE THE PLAYER CANNOT LOSE.
            // While the boss still has psyche left,
            while (bossEnemy.getPsyche() > 0) {
                // Print different flavor text for different stages in the battle.
                if (bossEnemy.getPsyche() > 666) {
                    cout << "You hear the Tuxedo Plant in your head. \"We are at your service old chum. How shall we proceed?\"" << endl;
                }
                else if (bossEnemy.getPsyche() > 333) {
                    cout << "You can hear the purring of the Rabid Docat. It brings an ultimate comfort." << endl;
                }
                else {
                    cout << "General Arbiter's voice echoes in your head. \"My friend. Reyalp is close to breaking. We need to save him. We'll have to pull all the stops on this next one. What's our move?\"" << endl;
                }

                // Prompt and get input for what the player wishes to do. They now only have 3 options.
                cout << "1. BEFRIEND! \n2. Check Party \n3. Check Enemy " << endl;
                cin >> userBattleInput;

                // If the player chose to befriend the boss, proceed with doing so. Have the boss attack the player, but have it do no damage.
                if (userBattleInput == 1) {
                    // Clear input
                    cin.clear();
                    cin.ignore();
                    // Flavor text
                    if (bossEnemy.getPsyche() > 666) {
                        cout << "You ask Reyalp to breathe and calm down. Things don't need to be this way." << endl;
                        cin.ignore();
                        cout << "\"N0! ST0P!! I D0N'T N33D YOU! THI$ W0RLD CAN B3 MINE!\"" << endl;
                        cin.ignore();
                    }
                    else if (bossEnemy.getPsyche() > 333) {
                        cout << "You try to reassure Reyalp. Everyone makes mistakes, after all!" << endl;
                        cin.ignore();
                        cout << "\"Y0U KN0W N0ooO-N0THING AB0UT ME!! Y0U'R3 JUST A B0R3D K1D IN FR0NT OF A SCR33N! THIS IS MY 3NTIRE 3XISTENCE! YOU DON'T C4**RE ABOUT ME!\"" << endl;
                        cin.ignore();
                    }
                    else {
                        cout << "You walk over to Reyalp as he flails about trying to damage you, and give him a firm hug. His cold armor is warmed by your aura." << endl;
                        cin.ignore();
                        cout << "The embrace lasts for an eternity." << endl;
                        cin.ignore();
                        cout << "..." << endl;
                        cin.ignore();
                        cout << "..." << endl;
                        cin.ignore();
                        cout << "..." << endl;
                        cin.ignore();
                        cout << "..." << endl;
                        cin.ignore();
                        cout << "..." << endl;
                        cin.ignore();
                        cout << "A Blue Aura forms around you two. Time is still." << endl;
                        cout << "..." << endl;
                        cin.ignore();
                        cout << "..." << endl;
                        cin.ignore();
                        cout << "You let go." << endl;
                        cin.ignore();
                    }
                    

                    // Update the bossEnemy's psyche. If the psyche dropped to below 0, update the psyche of the monster to be 0.
                    bossEnemy.setPsyche(bossEnemy.getPsyche() - 333);
                    if (bossEnemy.getPsyche() < 0) {
                        bossEnemy.setPsyche(0);
                    }

                    // Print results of the engagement
                    cout << bossEnemy.getCreatureName() << " took 333 psyche damage! " << endl;
                    cin.ignore();
                    cout << bossEnemy.getCreatureName() << " now has " << bossEnemy.getPsyche() << "/" << bossEnemy.getMaxPsyche() << " Psyche!" << endl;
                    cin.ignore();

                    // If the engagement resulted in the monster having 0 psyche, break from the loop and go straight to the ending battle conditions
                    if (bossEnemy.getPsyche() <= 0) {
                        break;
                    }

                    // Flavor text
                    if (bossEnemy.getPsyche() > 333) {
                        cout << "\"STOP! PLEASE JUST STOP!!\"" << endl;
                        cin.ignore();
                        cout << "Reyalp throws a mighty fist at you. It takes all of the rage he can build up." << endl;
                        cin.ignore();
                    }

                    else {
                        cout << "\"EN0UGH! WHY D0 Y0U K33P TRYING TO D0 THIS TO M33EEE!?? I'M JU$T A G4ME TO YOU!\"" << endl;
                        cin.ignore();
                        cout << "Reyalp shoots a tiny magical flame spark at you. It seemed to be the last of his energy." << endl;
                        cin.ignore();
                    }

                    // Have the boss attack the player, but have it do nothing.
                    cout << playerParty.getPartyMemberAt(0).getCreatureName() << " take 0 damage! " << endl;
                    cin.ignore();
                    cout << playerParty.getPartyMemberAt(0).getCreatureName() << " now have 999999/999999 HP!" << endl;
                    cin.ignore();
                }

                // If the player chose to view their party, display the party.
                else if (userBattleInput == 2) {
                    cout << endl;
                    cout << endl;
                    playerParty.printAllPartyMembers();
                    cout << endl;
                    cout << endl;
                }

                // If the player chose to view the enemy's stats, display the enemy stats.
                else if (userBattleInput == 3) {
                    cout << endl;
                    cout << endl;
                    bossEnemy.printStats();
                    cout << endl;
                    cout << endl;
                }

                // If the input was invalid, print an error message and clear cin
                else {
                    cout << "Sorry friend! That's one of them invalid inputs! " << endl;
                    cin.clear();
                    cin.ignore();
                }
            }

            // ONCE THIS LAST BATTLE IS OVER, THE BOSS FIGHT IS TRULY DONE NOW.
            // If the battle ended because the boss lost all psyche (which should be the only way the battle ended), print a message and exit the function.
            if (bossEnemy.getPsyche() <= 0) {
                cout << "Reyalp collapses on his knees. He takes off his helmet and throws it to the ground. A broken young man kneels before you." << endl;
                cin.ignore();
                cout << "But maybe he can be mended." << endl;
                return;
            }

            // If somehow the battle ended by some other means, print an error message. For debugging purposes.
            else {
                cout << "ERROR: FINALBOSSBATTLE WITH TRUE PROTAGONIST ENDED INCORRECTLY." << endl;
                return;
            }

        }
    }

    // If the player's party is somehow not applicable to any of the conditions, print an error message and exit the function. For debugging purposes
    else {
        cout << "ERROR: FINALBOSSBATTLE() FUNCTION FAILED; SIZE OF PARTY IS INVALID" << endl;
        return;
    }

}

// main function used for testing finalBossBattle()
int main() {
    srand(time(NULL));
    string flavorTextFile = "monsterFlavorText.txt";
    // Setup
    Item blankItem;
    Item healingPotion("Healing Potion", "Heals you for 50 HP", 50, 0, 0);
    Item blankInventory[1] = {blankItem};
    Item inventory1[5] = {healingPotion, healingPotion, healingPotion, healingPotion, healingPotion};
    Creature emperorReyalp("Emperor Reyalp", 0, blankInventory, 1000, 1000, 999, 999, 1500, 150, 0);
    Creature normalPlayer("Link Normal", 100, inventory1, 2000, 2000, 100, 100, 550, 650, 5);
    Creature scaryPlayer("Link Scary", 500, inventory1, 5000, 5000, 100, 100, 100000, 750, 5);
    Creature friendlyPlayer("Link Friendly", 500, inventory1, 10, 10, 100, 100, 3, 250, 5);
    Creature ally("Ally", 0, blankInventory, 150, 150, 5, 5, 250, 250, 0);

    Creature party1[7] = {normalPlayer, ally, ally, ally, ally, ally, ally};
    Creature party2[1] = {scaryPlayer};
    Creature party3[10] = {friendlyPlayer, ally, ally, ally, ally, ally, ally, ally, ally, ally};
    Party normalParty(party1, 7);
    Party scaryParty(party2, 1);
    Party friendlyParty(party3, 10);

    // Normal case: Player party is neither empty nor full (player only befriended some monsters)
    finalBossBattle(normalParty, normalParty.getCurrentPartySize(), emperorReyalp, flavorTextFile);

    // Normal Case: Player party is empty except for player (player befriended no monsters)
    finalBossBattle(scaryParty, scaryParty.getCurrentPartySize(), emperorReyalp, flavorTextFile);

    // Normal Case: Player party is full
    finalBossBattle(friendlyParty, friendlyParty.getCurrentPartySize(), emperorReyalp, flavorTextFile);

    return 0;
}