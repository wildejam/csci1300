// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project #3

// This driver file is used to test the useItem() function

#include <iostream>
#include <iomanip>
#include "Item.h"
#include "Creature.h"
#include "Party.h"

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

// Main function used for testing useItem()
int main() {
    // Setup (creating parties)
    Item healyPotion("Healy Potion", "heals u", 10, 0, 0);
    Item sword("sword", "hits things", 0, 10, 0);
    Item helmet("helmet", "safety first", 0, 0, 5);
    Item ring("ring", "put it on your finger", 5, 0, 7);
    Item bracelet("bracelet", "put it on your wrist", 10, 0, 10);
    Item necklace("necklace", "put it on your neck", 5, 0, 40);
    Item key("key", "opens something important", 0, 0, 0);
    Item diamond("diamond", "shiny", 10, 0, 0);
    Item pickaxe("pickaxe", "mines ores", 10, 0, 0);
    Item shield("shield", "protects you", 10, 0, 0);
    Item inventory1[10] = {healyPotion, sword, helmet, ring, bracelet, necklace, key, diamond, pickaxe, shield};
    int inventory1Size = 10;
    Creature human("Link", 50, inventory1, 10, 10, 7, 7, 5, 6, inventory1Size);
    Creature monster("Emu", 0, inventory1, 50, 25, 50, 40, 250, 50, inventory1Size);

    Creature party1[10] = {human, monster};
    Creature party2[10] = {human};
    Creature party3[10] = {human, monster, monster, monster, monster, monster, monster, monster, monster, monster};
    Party neutralParty(party1, 2);
    Party lonelyParty(party2, 1);
    Party funParty(party3, 10);

    // Normal Case: Player party has the player and one other member
    useItem(neutralParty, 2);
    // Normal Case: Player party has only the player
    useItem(lonelyParty, 1);
    // Normal Case: Player party is full
    useItem(funParty, 10);

    // Tests if player inventory item does not exist in future function calls
    useItem(neutralParty, 2);
    useItem(neutralParty, 2);
    useItem(neutralParty, 2);

}