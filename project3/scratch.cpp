#include <iostream>
#include <string>
#include "Item.h"
#include "Creature.h"
#include "Party.h"

using namespace std;

/*
finalBossBattle() - Function used to simulate the final boss battle in the game. Takes in the playerParty, modifies it to have 5 creatures, and takes in the boss.
    Also takes in a bossTrueForm creature, which replaces the boss depending on if the player has a full party/empty party.
    Modifies stats based on player actions. Is similar but distinct from the battle() function, and has specific narrative sequences. Does not return anything. Uses battle().
Parameters:
    playerParty - The array of creatures composing the player's party. Passed by reference. (Party)
    creaturesInParty - The amount of creatures stored in the playerParty[] array (int)
    bossbossEnemy - The bossEnemy boss that the player is fighting. Passed by reference (Creature)
    bossTrueForm - The more powerful version of the boss for special endings. Passed by reference. (Creature)
    textFileName - The name of the file containing the flavor text for the final boss (string)
Returns: Nothing
*/
void finalBossBattle(Party& playerParty, int creaturesInParty, Creature& bossbossEnemy, string textFileName) {
    // Declare variables
    int userBattleInput = 0;    // Variable used to store user input

    if (playerParty.getCurrentPartySize() > 1 && playerParty.getCurrentPartySize() < 10) {
        battle(playerParty, creaturesInParty, bossbossEnemy, textFileName);
    }

    else if (playerParty.getCurrentPartySize() == 1 && playerParty.getCurrentPartySize() == 10) {
        Item blankItem;
        Item blankInventory[1] = {blankItem};
        Creature opBoss("$$$R3Y4LP*****TH3*******D3FEND3R(%)$#$", 99999, blankInventory, 999999, 999999, 999, 999, 99999, 99999, 0);
        bossbossEnemy = opBoss;


    // When the battle begins, print the beginning battle flavor text for the monster being fought
    cout << findFlavorText(textFileName, bossbossEnemy.getCreatureName(), "beginningbattle") << endl;
    cout << endl;
    // MAIN BATTLE LOOP; WALKS THROUGH UNTIL EITHER PLAYER LOSES ALL HP OR bossEnemy MONSTER LOSES ALL HP, OR MONSTER LOSES ALL PSYCHE
    while (playerParty.getPartyMemberAt(0).getHealth() > 0 && bossEnemy.getHealth() > 0 && bossEnemy.getPsyche() > 0) {
        userBattleInput = 0;    // Reset battle input to be 0 every time the loop restarts

        // Print idle flavor text, then prompt and get input for what the player wishes to do
        cout << findFlavorText(textFileName, bossEnemy.getCreatureName(), "idle") << endl;
        cout << "What would you like to do? Choose a number: " << endl;
        cout << "1. Attack \n2. Befriend \n3. Use Item \n4. Check Party \n5. Check Monster" << endl;
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
            cout << bossEnemy.getCreatureName() << " took " << playerDamageToMonster << " damage!" << endl;
            cin.ignore();
            cout << bossEnemy.getCreatureName() << " now has " << bossEnemy.getHealth() << "/" << bossEnemy.getMaxHealth() << " HP!" << endl;
            cin.ignore();
            cout << endl;
            
            // If this attack caused the monster to reach 0 HP, break from the loop and go straight to ending battle conditions
            if (bossEnemy.getHealth() <= 0) {
                break;
            }

            // If the monster still has HP, have the monster take a turn by attacking the party.
            monsterAttacksParty(playerParty, playerParty.getCurrentPartySize(), bossEnemy, textFileName);
        }

        // If the player chose to befriend the monster
        else if (userBattleInput == 2) {
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
            cout << bossEnemy.getCreatureName() << " took 1 psyche damage!" << endl;
            cin.ignore();
            cout << bossEnemy.getCreatureName() << " now has " << bossEnemy.getPsyche() << "/" << bossEnemy.getMaxPsyche() << " Psyche!" << endl;
            cin.ignore();

            // If the engagement resulted in the monster having 0 psyche, break from the loop and go straight to the ending battle conditions
            if (bossEnemy.getPsyche() <= 0) {
                break;
            }

            // If the monster is still above 0 psyche, have the monster attack the player's party
            monsterAttacksParty(playerParty, playerParty.getCurrentPartySize(), bossEnemy, textFileName);
        }

        // If the player chose to use an item,
        else if (userBattleInput == 3) {
            cout << endl;
            // Walk the player through the Use Item sequence. If that function returned a 0, the item application was successful, so walk through a monster attack turn.
            // If the application was not successful, the monster does not get to have its turn yet, so this statement will be skipped over.
            if (useItem(playerParty, creaturesInParty) == 0) {
                cin.ignore();
                monsterAttacksParty(playerParty, playerParty.getCurrentPartySize(), bossEnemy, textFileName);
            }

        }

        // If the player chose to display the party stats, display them
        else if (userBattleInput == 4) {
            cout << endl;
            playerParty.printAllPartyMembers();
            cout << endl;
            cout << endl;
        }

        // If the player chose to display the bossEnemy stats, display them
        else if (userBattleInput == 5) {
            cout << endl;
            bossEnemy.printStats();
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

    }

    else {
        cout << "ERROR: FINALBOSSBATTLE() FUNCTION FAILED; SIZE OF PARTY IS INVALID" << endl;
    }

}