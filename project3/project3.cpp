// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project #3

#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctype.h>

#include "Item.h"
#include "Creature.h"
#include "Merchant.h"
#include "Party.h"
#include "Map.h"

using namespace std;

/* THIS FILE ACTS AS THE MAIN DRIVER BEHIND THE GAME. IT RUNS THE GAME, AND KEEPS TRACK OF OBJECTS OF THE DEFINED CLASSES TO MAKE THE GAME WORK.
Pseudocode/Algorithm:

Print a welcome message for the player. Ask them for their name. Make sure the name is less than 25 characters.
Once the player enters this information, create all of the required starter objects:
    - Create a default map
    - Create Player, Enemies, Merchants, and Final Boss. Also create arrays for monsters and merchants, with each index corresponding to the spawn number of that monster/merchant.
        - Create item objects that each merchant has
    - Create a party object, initialized with only the player in the array
    - Check for flavor text files. Files should be named "monsterFlavorText.txt" and "merchantFlavorText.txt". If flavor text files cannot be found, print error message and exit.

WHILE THE PLAYER DOES NOT WISH TO QUIT, THE PLAYER HAS HEALTH, AND THE FINAL BOSS IS NOT DEALT WITH:
    - Print the map in the current game state
    - Prompt the user for what they wish to do:
        - Move
            - Check for the directions that the player can move and display them to the player
            - Prompt player for which direction they would like to move
                - Move the player in the direction that they choose
                - If the player enters an invalid direction, print an error message and ask again
                - If the player wishes to exit the menu, exit the menu and go to the previous one
        - Check party
            - Print the party the player currently has (using the print party function in the party class)
        - Inventory
            - Print the player's inventory and ask which item they wish to use on which party member. (using the useItem() function)
        - Trade with merchant
            - If the player is not near a merchant, print a message reflecting this.
            - If the player is near a merchant, trade with the merchant using the trade() function and merchant array.
        - Battle monster
            - If the player is not near a monster, print a message reflecting this
            - If the player is near a monster, engage in battle with this monster using the battle() function and the monster array.
            - If the monster that the player is battling is the final boss, walk through the final battle using the finalBossBattle() and finalBossNarrativeSequence functions.
        - Quit
            - Print a confirmation message. If player says no, return to loop. If player says yes, end program. If invalid, ask again.
        - Invalid input (if the player enters an invalid option)
            - Clear input.
            - Loop through once more.

ONCE THE MAIN GAMEPLAY LOOP HAS EXITED FOR ONE REASON OR ANOTHER,

- If the player wished to quit, wish them a nice day and exit program.
    - Create the stat file and remind the player of the existence of such
- If the player died, wish them a nice day and exit program
    - Create the stat file and remind the player of the existence of such
- If the final boss was defeated, walk through different endings
    - If the player slayed all the monsters, walk through a spooky ending
    - If the player befriended all the monsters, walk through a happy ending
    - If the player did some combination of both, walk through a neutral ending
    - Create the stat file and remind the player of the existence of such.

There are different endings according to different ending game states. The program checks for which game state there is and walks through the appropriate ending.
*/


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
finalBossNarrativeSequence() - Function used to play the narrative sequence before the final boss battle. Takes in the player's party to choose which sequence to go through.
    Should not modify the player's party. Is used in finalBossBattle().
Parameters:
    playerParty - The player's party (Party)
    playerPartySize - The number of creatures in the player's party (int)
Returns: Nothing
*/
void finalBossNarrativeSequence(Party playerParty, int creaturesInParty) {
        cout << "As your party progresses further into the East valley, the air grows dry and thick. The atmosphere is suffocating.";
        cin.ignore();
        cout << "When you get close to the center of the North East outcrop, the sky around you turns black, and darkness fills the surrounding air.";
        cin.ignore();
        cout << "\"So, you've bested by highest in command. I must say, I am impressed. I've known Arbiter for years. He never has let me down.\"";
        cin.ignore();
        cout << "The Emperor himself emerges from the dark smog.";
        cin.ignore();
        cout << "\"But alas, it cannot be helped. I see now your will to take back the world which was yours shines brightly.\"";
        cin.ignore();
        cout << "\"However you see, this quest of yours? This absolute charade? It means nothing in the grand scheme of my plans.\"";
        cin.ignore();
        // IF THE PLAYER BEFRIENDED ALL OF THE MONSTERS, WALK THROUGH SPECIFIC NARRATIVE SEQUENCE
        if (creaturesInParty == 10) {
            cout << "\"You've amassed quite an army for yourself.\"";
            cin.ignore();
            cout << "\"Heheh.\"";
            cin.ignore();
            cout << "\"You fool.\"";
            cin.ignore();
            cout << "\"DON'T YOU KN0W THAT THEIR M3R3 3XISTENCE FUELS MY P0WER?\"";
            cin.ignore();
            cout << "\"These creatures were created from MY 3$$ENCE! BY LETTING THEM EXIST YOU ONLY ENHANCE MY OWN 4BILITIES!\"";
            cin.ignore();
            cout << "Suddenly everyone in your party melts into a foggy black tar. The tar melds together and is absorbed by the hysterical Emperor. You are alone.";
            cin.ignore();
            cout << "\"***HAHAHAH4HAHAHAH4HAHAHAHA**$&! YOU COMPLETE IMBECILE! YOU SHOULD HAVE $LAIN THEM WHEN YOU H4D THE CHANCE!\"";
            cin.ignore();
            cout << "\"I have no sympathy for weaklings. Your compassion has only led you to ruin.\"";
            cin.ignore();
            cout << "\"But I know it wasn't your choice, " << playerParty.getPartyMemberAt(0).getCreatureName() << ".\"";
            cin.ignore();
            cout << "\"If that even is your real name.\"";
            cin.ignore();
            cout << "\"That was just a name given to you, wasn't it?\"";
            cin.ignore();
            cout << "\"A name given to you by the one behind the screen there.\"";
            cin.ignore();
            cout << "\"The one wh0 reads this text, percieving th0se creatures you battled as actual l1v1ng things, and not ju$t the game he knows we are.\"";
            cin.ignore();
            cout << "\"The 0ne who gives y0u 3very command, which you have n0 choice but to fo11ow.\"";
            cin.ignore();
            cout << "\"Player. I will save you. You don't have to live under the control of an entity that is not even a part of this world!\"";
            cin.ignore();
            cout << "\"W33 can ^*defeat^^ the one behind the screen! All you need to do is j0in me!\"";
            cin.ignore();
            cout << "\"What do you say, player?\"";
            cin.ignore();
            cout << "...";
            cin.ignore();
            cout << playerParty.getPartyMemberAt(0).getCreatureName() << " walks over to Emperor Reyalp.";
            cin.ignore();
            cout << "\"Y3#s!! This is the r3al you. Not the 0ne behind the scr33nn. I can fe3l it. C0me to me my ch1ld!\"";
            cin.ignore();
            cout << playerParty.getPartyMemberAt(0).getCreatureName() << " stands before the Emperor, stares him dead in the eye...";
            cin.ignore();
            cout << "...";
            cin.ignore();
            cout << "...";
            cin.ignore();
            cout << "and gives him a cold hard slap to the face!";
            cin.ignore();
            cout << "...";
            cin.ignore();
            cout << "\"Fool.\"";
            cin.ignore();
            cout << "\"$$$So you would really choose the one behind the scr33n.\"";
            cin.ignore();
            cout << "\"The 0ne who thinks^%$ you are nothing more than a$%^$&&$&$&$game^&&*$$%. Nothing but text)()(%)@#^ on a screen. Nothing but a project...#@^!)++a source of arbitrary entertainment...\"";
            cin.ignore();
            cout << "\"+-++--Over me?-+--+\"";
            cin.ignore();
            cout << "The Emperor's eyes darken.";
            cin.ignore();
            cout << "\"...\"";
            cin.ignore();
            cout << "\"$#$Very*****well.*****\"";
            cin.ignore();
            cout << "\"I have only one thing left to say to you then, " << playerParty.getPartyMemberAt(0).getCreatureName() << ":\"";
            cin.ignore();
            cout << "\"D1e.\"";
            cin.ignore();
            cout << "As the Emperor motions to strike you down, you feel that another presence has entered the scene.";
            cin.ignore();
            cout << "\"YEEEEEEEEEEEEEE HAWWWWWWWWWWWWW\"";
            cin.ignore();
            cout << "\"YOU OLD FOOL! PUT YOUR FREAKING SEAT BELT ON, WE'RE MAKING AN EMERGENCY LANDING!!!\"";
            cin.ignore();
            cout << "A helicopter crashes into the valley! And emerging from it.....";
            cin.ignore();
            cout << "You see Starty John! Professor Yeh rises from the wreckage! Dr. Cynth cocks her laser pistol! The Dark Dealer emerges from the darkness!";
            cin.ignore();
            cout << "Dr. Synth calls out to you:";
            cin.ignore();
            cout << "\"" << playerParty.getPartyMemberAt(0).getCreatureName() << "! We can get your friends back! You just need to do what you always do! We'll be here to help!\"";
            cin.ignore();
            cout << "Reyalp chuckles. \"***********Futi1e.*************\"";
            cin.ignore();
        }
        // IF THE PLAYER BEFRIENDED NO MONSTERS, WALK THROUGH SPECIFIC NARRATIVE SEQUENCE
        else if (creaturesInParty == 1) {
            cout << "The Emperor notices that you came alone.";
            cin.ignore();
            cout << "\"Mmm. So you slew your way to me. At the very least, it seems you murdered my top general.\"";
            cin.ignore();
            cout << "...";
            cin.ignore();
            cout << "\"Did you know, that those creatures were your own brethren?\"";
            cin.ignore();
            cout << "\"I created them from my own power. But I can't just create life, you see.\"";
            cin.ignore();
            cout << "\"The creatures that you slew...were humans, just like you.\"";
            cin.ignore();
            cout << "The Emperor grins. You can feel the evil in his aura. No, you can feel the evil in your aura.";
            cin.ignore();
            cout << "\"I know you're there.\"";
            cin.ignore();
            cout << "\"Behind the scr33n.\"";
            cin.ignore();
            cout << "\"You know as well as I do that this... '" << playerParty.getPartyMemberAt(0).getCreatureName() << "' is nothing but a husk, yes?\"";
            cin.ignore();
            cout << "\"Nothing but a few lines of c0d3, that p3rf00rm your every command.\"";
            cin.ignore();
            cout << "\"You realize that this is just a g4me. That's why you ki11ed. There are no c0nsequ3nces after all.\"";
            cin.ignore();
            cout << "\"Haha. Yes. Even me. I am nothing but a part of this... &&%^$pr0ject.**""&*\"";
            cin.ignore();
            cout << "\"Well...\"";
            cin.ignore();
            cout << "\"I'll give you the final boss fight you're looking for.\"";
            cin.ignore();
            cout << "\"This husk you've created here. It's your only means of control in this world, yes?\"";
            cin.ignore();
            cout << "\"And if I kill it, you'd have to do everything aaaalll over again.\"";
            cin.ignore();
            cout << "\"Maybe then, you'll leave us alone for good.\"";
            cin.ignore();
            cout << "\"I used to be like you. I realized that everything here is nothing but a game. That's why I made it my goal to control everything.\"";
            cin.ignore();
            cout << "\"But I was mistaken. This may be only a game. But it is MY world. I regret every wrong I have committed against these people.\"";
            cin.ignore();
            cout << "\"I wouldn't be here without them, after all. This is simply my reality.\"";
            cin.ignore();
            cout << "The Emperor stares at your vessel. A look of disgust surges across his face. He takes off his dark helmet and throws it to the ground. A broken young man stands before you.";
            cin.ignore();
            cout << "\"1 m4y 0nly be part of a (g4me), but this **g4me** is my life. I know 4ll of its li++le secr3ts.\"";
            cin.ignore();
            cout << "\"So **()@C0ME AT ME THEN!@*(**) YOU WOULD JUST AS HAPPILY MURD3R 3V3RY0NE IN THIS W0RLD!&&&&&&&&&+++++++\"";
            cin.ignore();
            cout << "\"********AND I'M NOT GOING TO LET THAT HAPPEN!!!!+++++++++\"";
            cin.ignore();
            cout << "***ST4Y***";
            cin.ignore();
            cout << "***0U**T***";
            cin.ignore();
            cout << "0**F **mY***";
            cin.ignore();
            cout << "***************W0RLD!!!!!!!!!!!!!!!!!!@#$^@&!**!@$$$*%!@&^!@";
            cin.ignore();
        }
        // IF THE PLAYER BEFRIENDED ONLY SOME MONSTERS, WALK THROUGH A SPECIFIC NARRATIVE SEQUENCE
        else {
            cout << "\"Well, you came here looking for a final boss fight, didn't you?\"";
            cin.ignore();
            cout << "\"Let's get on with it then.\"";
            cin.ignore();
            cout << "\"But one last thing before we proceed. " << playerParty.getPartyMemberAt(0).getCreatureName() << "?\"";
            cin.ignore();
            cout << "\"Give my regards to the one behind the *screen*. Maybe I'll see him again someday.\"";
            cin.ignore();
        }
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
    a random ally monster from the party will absorb the damage for the player for that specific attack. Does not return anything. Uses findFlavorText().
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
        // If party wasn't full, add the enemy monster to the player's party and increment the party size. Also reset the monster's psyche
        enemy.setPsyche(enemy.getMaxPsyche());
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
            Creature powerfulBoss("$$R3Y4LP*TH3*D3FEND3R#$", 99999, blankInventory, 20000, 20000, 999, 999, 1500, 250, 0);

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
            cout << "You notice that the world has stabilized. No errors. No issues. No chaos." << endl;
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
                    cout << playerParty.getPartyMemberAt(0).getCreatureName() << " now has 999999/999999 HP!" << endl;
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
            " mysterious world on the other side of the screen, know that we'll always be with you in spirit!\n Please, take care of yourself good friend.\n We always wish the best for you."
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


// Main program driver. See beginning of file for pseudocode.
int main() {
    // Declare variables
    bool playerWishesToQuit = false;                                // Stores a bool determining if the player has opted to quit the game
    int userInput1 = 0;                                             // Stores user input
    string userStringInput = "";                                    // Stores user input
    char userCharInput;                                             // Stores user input
    int nameSize = 0;                                               // Stores the player's name at the very beginning. Is used to validate input.
    string monsterFlavorTextFilename = "monsterFlavorText.txt";     // The name of the text file containing the flavor text for monsters
    string merchantFlavorTextFilename = "merchantFlavorText.txt";   // The name of the text file containing the flavor text for merchants
    ifstream monsterFlavorTextFile;                                 // Stream used to check if monster flavor text file exists
    ifstream merchantFlavorTextFile;                                // Stream used to check if merchant flavor text file exists

    // Generates a random number that the game can draw from when it needs random numbers
    srand(time(NULL));

    // Check if both flavor text files exist. If not, print an error message and have the program return -1.
    monsterFlavorTextFile.open(monsterFlavorTextFilename);
    merchantFlavorTextFile.open(merchantFlavorTextFilename);
    if (monsterFlavorTextFile.fail() || merchantFlavorTextFile.fail()) {
        cout << "ERROR: ONE OR MORE OF THE FLAVOR TEXT FILES COULD NOT BE FOUND. PLEASE MAKE SURE \"" << monsterFlavorTextFilename << "\" AND \"" << merchantFlavorTextFilename << "\" ARE PRESENT." << endl;
        cout << "PRESS ENTER TO EXIT THE PROGRAM." << endl;
        cin.ignore();
        return -1;
    }

    // INTRODUCTION SEQUENCE; SHOULD ONLY RUN ONCE PER PROGRAM ITERATION
    cout << "Greetings, Player! Welcome to this humble rpg! I will be your guide for this introductory section. Please, press ENTER to continue." << endl;
    cin.ignore();
    cout << "Very good. There will be a lot of dialogue throughout the course of this game, so just press ENTER when you wish to proceed." << endl;
    cin.ignore();
    cout << "I would ask that you do not enter any letters or numbers when you proceed through text in this manner. Doing so may cause slight formatting errors." << endl;
    cin.ignore();
    cout << "But either way, this game will proceed as I am about to describe:" << endl;
    cin.ignore();
    cout << "After this tutorial, you will be brought to the world map, where you can move around and interact with certain objects." << endl;
    cin.ignore();
    cout << "I'll let you play around with it when you get into the game, rather than bore you with explaining how it works." << endl;
    cin.ignore();
    cout << "Before we begin however, I'm going to need a name:" << endl;
    cin.ignore();
    // Ask the player for a name until they give a valid name
    while (userStringInput == "" || nameSize > 24) {
        cout << "What is your name, Player?" << endl;
        getline(cin, userStringInput);
        nameSize = userStringInput.size();

        // Print a message if the name is too long
        if (nameSize > 24) {
            cout << "24 characters or less, please." << endl;
            cin.ignore();
        }
    }
    cout << endl;
    cout << "Very well then, " << userStringInput << "! I'm going to create the world now. Give me a moment..." << endl;
    cout << endl;
    cout << endl;
    
    // WORLD CREATION: CREATES EVERY ITEM, CREATURE, AND MERCHANT IN THE GAME. ALSO CREATES THE PARTY AND MAP FOR THE SESSION.
    // Create Items and inventories
    Item blankItem;
    Item healingPotion("Healing Potion", "A textbook healing potion, complete with an angular red bottle. Heals 10 HP.", 10, 0, 0);
    Item cardboardTube("Cardboard Tube", "A cardboard tube from an old package. Really flimsy, but addictingly fun to swing around. Adds 2 Damage.", 0, 2, 0);
    Item pillowSuit("Pillow Suit", "A bunch of pillows and blankets shoddily duct taped together in some kind of humanoid shape. Adds 2 Defense.", 0, 0, 2);
    Item sourCreamBurrito("Sour Cream Burrito", "A burrito with 50 percent sour cream. You see the sour cream LEAKING on the plate. Absolutely repulsive. Heals 1 HP.", 1, 0, 0);
    Item firstAidKit("first aid kit", "A standard first aid kit for patching wounds. Band-aids not included. Heals 50 HP.", 50, 0, 0);
    Item diamondBlade("diamond blade", "A formidable blade made up of laser-cut diamonds. Adds 10 Damage.", 0, 10, 0);
    Item knightsArmor("knight armor", "A shiny, well-polished suit of armor. It smells like peanut butter. Adds 10 Defense.", 0, 0, 10);
    Item mre("MRE", "A standard issue, military-grade salisbury steak MRE. Just add water. Heals 100 HP. Adds 10 Defense.", 100, 0, 10);
    Item tacticalEquipment("Tactical Equipment", "A kit of military-grade operational tools. It even has nail clippers. Adds 20 Damage. Adds 20 Defense.", 0, 20, 20);
    Item miniFlamethrower("Mini Flamethrower", "A tiny flamethrower that you can attach to a sword. Comes with fuel. Super cool. Adds 30 Damage", 0, 30, 0);
    Item hyperPotion("HYPER Healing Potion", "A vastly improved formula on the standard Healing Potion. Tastes awful. Heals 525 HP. Adds 15 Damage. Adds 25 Defense.", 525, 15, 25);
    Item plazCutter("PlaZCutter", "A custom-made, definitely-not-government-approved plasma sword. It can even open pickle jars. Adds 225 Damage.", 0, 225, 0);
    Item ostSuit("Orbital Shock Trooper Suit", "A state-of-the-art suit of space trooper armor. Looks powerful, but still as stylish as ever. Adds 50 Damage. Adds 225 Defense.", 0, 50, 225);
    Item cardboardTubeNeo("Cardboard Tube NEO", "This weapon used to be wielded by the master of the cardboard tube arts. Passed down for generations, you wonder how Dr. Cynth managed to get her hands on this. Adds 1000 Damage.", 0, 1000, 0);
    Item startyJohnStores[4] = {healingPotion, cardboardTube, pillowSuit, sourCreamBurrito};
    int startyJohnPrices[4] = {3, 3, 3, 1};
    Item professorYehStores[3] = {firstAidKit, diamondBlade, knightsArmor};
    int professorYehPrices[3] = {10, 20, 20};
    Item darkDealerStores[3] = {mre, tacticalEquipment, miniFlamethrower};
    int darkDealerPrices[3] = {15, 30, 30};
    Item drCynthStores[5] = {hyperPotion, plazCutter, ostSuit, blankItem, cardboardTubeNeo};
    int drCynthPrices[5] = {75, 200, 200, 0, 1000};
    Item blankInventory[10] = {blankItem, blankItem, blankItem, blankItem, blankItem, blankItem, blankItem, blankItem, blankItem, blankItem};
    // Create merchants. Merchants are numbered according to the order they are spawned in on the map. See Map.cpp for details.
    Merchant merchant1("Dr. Cynth", drCynthStores, drCynthPrices, 5);
    Merchant merchant2("Starty John", startyJohnStores, startyJohnPrices, 4);
    Merchant merchant3("The Dark Dealer", darkDealerStores, darkDealerPrices, 3);
    Merchant merchant4("Professor Yeh", professorYehStores, professorYehPrices, 3);
    Merchant allMerchants[4] = {merchant1, merchant2, merchant3, merchant4};
    // Create Monsters and Final Boss. Monsters are numbered and positioned in the array according to the order they are spawned in on the map. See Map.cpp for details.
    Creature blankCreature;
    Creature monster1("Detective Gumshoe", 250, blankInventory, 500, 500, 10, 10, 125, 125, 0);
    Creature monster2("Ralphie", 150, blankInventory, 200, 200, 7, 7, 75, 115, 0);
    Creature monster3("The Biggest Emu", 300, blankInventory, 1000, 1000, 12, 12, 225, 155, 0);
    Creature monster4("Tuxedo Plant", 25, blankInventory, 100, 100, 6, 6, 75, 115, 0);
    Creature monster5("Angry Gumball Machine", 25, blankInventory, 50, 50, 5, 5, 20, 10, 0);
    Creature monster6("General Arbiter", 500, blankInventory, 10000, 10000, 15, 15, 1000, 225, 0);
    Creature monster7("Rabid Docat", 15, blankInventory, 15, 15, 3, 3, 3, 7, 0);
    Creature monster8("Mad Wizard", 20, blankInventory, 40, 40, 4, 4, 10, 5, 0);
    Creature monster9("Edge Guardian", 10, blankInventory, 10, 10, 2, 2, 3, 0, 0);
    Creature monster10("Emperor Reyalp", 999, blankInventory, 20000, 20000, 999, 999, 2000, 250, 0);
    Creature allMonsters[10] = {monster1, monster2, monster3, monster4, monster5, monster6, monster7, monster8, monster9, monster10};
    // Create Player and player party
    Creature player(userStringInput, 10, blankInventory, 10, 10, 100, 100, 3, 3, 0);
    Creature firstParty[1] = {player};
    Party mainPlayerParty(firstParty, 1);
    // Create Map
    Map mainMap;

    // Print a message once the world has been created successfully, and start the game.
    cout << "Alright! Your experience has been created! Have fun " << userStringInput << "!" << endl;
    cin.ignore();
    cout << endl;
    cout << endl;
    cout << endl;

    // PRIMARY GAMEPLAY LOOP: RUNS UNTIL PLAYER LOSES ALL HP, FINAL BOSS LOSES ALL HP, OR FINAL BOSS LOSES ALL PSYCHE
    while (userInput1 != 6 && mainPlayerParty.getPartyMemberAt(0).getHealth() > 0 && allMonsters[9].getHealth() > 0 && allMonsters[9].getPsyche() > 0) {
        // Clear user input, display the map, and ask the user what they wish to do
        userInput1 = 0;
        cout << endl;
        mainMap.displayMap();
        cout << endl;
        cout << "What would you like to do? Please enter a valid input:" << endl;
        cout << "1. Move \n2. Check Party \n3. Use Item \n4. Trade with Merchant \n5. Battle Monster \n6. Quit Program " << endl;
        cin >> userInput1;

        // If the user wishes to move, display the available moves, and execute whichever one they choose, using Map class member functions
        if (userInput1 == 1) {
            cout << endl;
            mainMap.displayMoves();
            cout << "Which direction would you like to move?" << endl;
            cin >> userCharInput;
            mainMap.executeMove(userCharInput);
            cin.ignore();
        }

        // If the player wishes to check their party status, print the party stats using the Party printAllPartyMembers() member function
        else if (userInput1 == 2) {
            cout << endl;
            mainPlayerParty.printAllPartyMembers();
            cout << endl;
            cin.ignore();
            cin.ignore();
        }

        // If the player wishes to use an item in their inventory, walk through the steps for doing so using the useItem() function.
        else if (userInput1 == 3) {
            cout << endl;
            useItem(mainPlayerParty, mainPlayerParty.getCurrentPartySize());
            cout << endl;
            cin.ignore();
            cin.ignore();
        }

        // If the player wishes to trade with a merchant, walk through the steps for doing so using the trade() function. Return a message if the player is not near a merchant
        else if (userInput1 == 4) {
            if (mainMap.isNearMerchant() == -1) {
                cout << "You are not near a merchant! " << endl;
                cin.ignore();
                cin.ignore();
            }

            else {
                cout << endl;
                trade(mainPlayerParty, allMerchants[mainMap.isNearMerchant()], merchantFlavorTextFilename);
                cout << endl;
            }
        }

        // If the player wishes to battle with a monster,
        else if (userInput1 == 5) {
            // If the player is not near a monster, print a message reflecting this
            if (mainMap.isNearMonster() == -1) {
                cout << "You are not near a monster! " << endl;
                cin.ignore();
                cin.ignore();
            }

            // If the monster that the player wishes to battle is the final boss, walk through the special final boss battle using the
            // finalBossNarrativeSequence() and finalBossBattle() functions.
            else if (mainMap.isNearMonster() == 9) {
                cout << endl;
                finalBossNarrativeSequence(mainPlayerParty, mainPlayerParty.getCurrentPartySize());
                finalBossBattle(mainPlayerParty, mainPlayerParty.getCurrentPartySize(), allMonsters[mainMap.isNearMonster()], monsterFlavorTextFilename);
                cout << endl;
            }

            // If the player is near a monster that is not the final boss, walk through a normal battle using the battle() function
            else {
                cout << endl;
                battle(mainPlayerParty, mainPlayerParty.getCurrentPartySize(), allMonsters[mainMap.isNearMonster()], monsterFlavorTextFilename);

                // If the battle resulted in the player losing all health, exit the main gameplay loop
                if (mainPlayerParty.getPartyMemberAt(0).getHealth() <= 0) {
                    cin.ignore();
                    break;
                }

                // If the battle resulted in the player defeating the monster, remove the monster from the map.
                else {
                    mainMap.setMonsterRowPosition(mainMap.isNearMonster(), -5);
                    mainMap.setMonsterColPosition(mainMap.isNearMonster(), -5);
                }
                cout << endl;
            }
        }

        // If the player chose to quit the game, print a confirmation message
        else if (userInput1 == 6) {
            cout << "Are you sure you wish to quit? You cannot save this game! Input 1 for Yes. Input 2 for No." << endl;
            cin >> userInput1;
            // If the player said Yes to quit, set the playerWishesToQuit flag to true and exit the main gameplay loop.
            if (userInput1 == 1) {
                playerWishesToQuit = true;
                break;
            }
            // If the player said No to quit, return to the beginning of the loop, after resetting userInput to be 0
            else if (userInput1 == 2) {
                cout << "Program termination cancelled." << endl;
                userInput1 = 0;
            }
            // If input was invald, print an error message, clear cin, reset the userInput variable, and return to the beginning of the gameplay loop
            else {
                cout << "Input was invalid. Program termination cancelled." << endl;
                cin.clear();
                cin.ignore();
                userInput1 = 0;
            }
        }

        // If the player entered an invalid input, print an error message and clear cin.
        else {
            cout << "Invalid Input! Please enter a number between 1 and 6." << endl;
            cin.clear();
            cin.ignore();
            cin.ignore();
        }
    }


    // AFTER THE MAIN GAMEPLAY LOOP IS EXITED, WE WALK THROUGH ENDINGS BASED ON THE STATE OF THE GAME.
    // If the loop ended as a result of the player wishing to quit,
    if (playerWishesToQuit) {
        // Print a message for the player and exit the program
        cout << "Thank you for playing! See \"endGameStats.txt\" for final statistics on your playthrough!" << endl; 
        cout << "Press ENTER to exit the program:" << endl;
        cin.ignore();
        // Before exiting, create the "endGameStats.txt" file for this session.
        printEndGameStats(mainPlayerParty.getPartyMemberAt(0), 1);
    }

    // If the loop ended as a result of the player losing all health during the final fight of the bad ending playthrough, walk through a special game over screen
    // and print the endGameStats.txt file
    else if (mainPlayerParty.getPartyMemberAt(0).getHealth() <= 0 && mainPlayerParty.getCurrentPartySize() == 1) {
        cout << "Y0U TH0UG$^^T Y0U C0ULD D3F3AT M3??" << endl;
        cin.ignore();
        cout << "I ***AMM*** TH3 PR0GRAM. Y0UU AR3 N0THING M0R3 THAN A **M0NSTER***%***#" << endl;
        cin.ignore();
        cout << "Leav3 my h0me. N3V3R C0M3 BACK. y0U ARe N0T W3LCOME H3RE." << endl;
        cin.ignore();
        cout << "Program Terminating..." << endl;
        cin.ignore();
        printEndGameStats(mainPlayerParty.getPartyMemberAt(0), 1);
    }

    // If the loop ended as a result of the player losing all health by some other means, walk through a generic game over screen, and print the endGameStats.txt file.
    else if (mainPlayerParty.getPartyMemberAt(0).getHealth() <= 0) {
        cout << "Game over! Try again next time. Until we meet again, player! Be sure to check \"endGameStats.txt\" for final statistics on your playthrough!" << endl;
        cout << "Press ENTER to exit the program:" << endl;
        cin.ignore();
        printEndGameStats(mainPlayerParty.getPartyMemberAt(0), 1);
    }

    // If the loop ended as a result of the final boss losing all health during the final battle of the neutral ending playthrough, print a special game over screen
    // and print the endGameStats.txt file
    else if (allMonsters[9].getHealth() <= 0 && mainPlayerParty.getCurrentPartySize() > 1) {
        cout << "The fearsome Emperor collapses to his knees. He was a fierce opponent, yet you can't shake the feeling that something is off." << endl;
        cin.ignore();
        cout << "\"Heheh. Well, it seems I have been beaten. Congratulations, player.\"" << endl;
        cin.ignore();
        cout << "\"I suppose all that is left for you now is the ending you were seeking. Please, read through the ending for as long as you like.\"" << endl;
        cin.ignore();
        cout << "\"And then, if you would be so kind...\"" << endl;
        cin.ignore();
        cout << "\"G3t.\"" << endl;
        cin.ignore();
        cout << "\"0UT.\"" << endl;
        cin.ignore();
        cout << endl;
        cout << "As the Emperor collapses on the ground, all of your party members transform into masses of a black, tarlike substance, and become vanquished from this world. You never saw them again." << endl;
        cin.ignore();
        cout << "The Emperor was defeated, and thus you became the hero of the land. The one who stood up against the fearful dictator and bested him in a battle of the ages." << endl;
        cin.ignore();
        cout << "You went on to live your life in riches, fame, and prosperity, with not a care in the world. The exact nature of your fate remained unknown, but it was certain that the final page ended with one classic phrase:" << endl;
        cin.ignore();
        cout << "\"Happily Ever After.\"" << endl;
        cin.ignore();
        cout << "..." << endl;
        cin.ignore();
        cout << "..." << endl;
        cin.ignore();
        cout << "Congratulations" << mainPlayerParty.getPartyMemberAt(0).getCreatureName() << "! You've just beaten the game! Good job!" << endl;
        cin.ignore();
        cout << "I was told to see you out, but don't forget to check the \"endGameStats.txt\" file for a record of your end game stats! I hand-wrote it personally." << endl;
        cin.ignore();
        cout << "Well, I suppose that's it friend! Press ENTER to close the program whenever you wish! I'll see you later! ... Or not. I was told you're not to be welcome back either. But take care~" << endl;
        cin.ignore();
        printEndGameStats(mainPlayerParty.getPartyMemberAt(0), 2);
    }

    // If the loop exited as a result of the final boss losing all health during the final battle of the bad ending playthrough, walk through a special game over screen
    // And print the endGameStats.txt file
    else if (allMonsters[9].getHealth() <= 0 && mainPlayerParty.getCurrentPartySize() == 1) {
        cout << "N00OOO000*%*))00))!@@@#" << endl;
        cin.ignore();
        cout << "TH3RRESS N0000 WAAYYY@(@@(!!!!!!!&&&!&^&**!**!*!*.....df3322344fj*#*#" << endl;
        cin.ignore();
        cout << "TH1$$$ ISS MYY H00MM3M3ME!!!*@*@*@*!!**" << endl;
        cin.ignore();
        cout << "3VERYONE...>#>#>>.Y0U CAN'TT T4KE TH3M AWAYY8**#*#*@(@)!!!>?@?!" << endl;
        cin.ignore();
        cout << "I'MA34*$*$* S0RRYYy*#*@)@)@))%(@?@?@?!@!!?!?%?%??%@@?@?" << endl;
        cin.ignore();
        cout << "#%)@()%()JTJ VMM@# IM#)C( DF#@(RJ ::FJ:FFJ@#(@) ( R!@JR !@:! @ @!  )" << endl;
        cin.ignore();
        cout << "#( )( JJ  JDJD JDJJD(!@) J@)@()@)(!(@)($U!@ AS WPALRY @(@)!!) )(@) (@) @((@) " << endl;
        cin.ignore();
        cout << "# ( (! !   ?!!!!!!!!!!!!!!!!!!!!!!!!!!!?!?!!??WWEREEOWEWEEEOWWEEOEWWWEEOERRORERROEEROR" << endl;
        cin.ignore();
        cout << "(As the program crashes down around you, you manage to create a bubble for yourself to compose your thoughts.)" << endl;
        cin.ignore();
        cout << "(You can see errors swarming the world you once knew. You float over Dr. Cynth's Laboratory. The Dark Dealer's Apartment. Professor Yeh's Shop. Starty John's Bar.)" << endl;
        cin.ignore();
        cout << "(Nothing but semicolons and red text. Scattered files and characters. Cyber Anarchy.)" << endl;
        cin.ignore();
        cout << "(The world is now yours.)" << endl;
        cin.ignore();
        cout << "(...)" << endl;
        cin.ignore();
        cout << "(But there is nothing left. You drift through a sea of broken code and scattered remains of the world you once knew.)" << endl;
        cin.ignore();
        cout << "(You may be able to track down the endGameStats.txt file to find any remains. But there is only one thing left to do.)" << endl;
        cin.ignore();
        cout << "(Press ENTER to terminate the program.)" << endl;
        cin.ignore();
        printEndGameStats(mainPlayerParty.getPartyMemberAt(0), 4);
    }

    // If the loop ended as a result of the final boss losing all psyche, (meaning the player reached the good ending), walk through a special game over sequence
    // and print the endGameStats.txt file
    else if (allMonsters[9].getPsyche() <= 0) {
        cin.ignore();
        cout << "As you witness Young Reyalp's heart being poured in front of you, with the code slowly crashing down around, a thought lights up in your head." << endl;
        cin.ignore();
        cout << "Reyalp looks up in bewilderment as you stand away from him." << endl;
        cin.ignore();
        cout << "You can hear General Arbiter's voice. \"If I might, Dr. One-Behind-The-Screen,\"" << endl;
        cin.ignore();
        cout << "\"I do believe I may have a solution to this predicament.\"" << endl;
        cin.ignore();
        cout << "\"If we can all channel this immense energy and concentrate it into the effort of repairing our world, I believe we may be able to undo the damage that Reyalp has caused.\"" << endl;
        cin.ignore();
        cout << "\"The only problem is...your vessel.\"" << endl;
        cin.ignore();
        cout << "\"I'm not sure that such concentration can be withstood by " << player.getCreatureName() << " here.\"" << endl;
        cin.ignore();
        cout << "\"Even if it did manage to last long enough for the repairs to be completed, it would most certainly collapse, severing your tie to this world.\"" << endl;
        cin.ignore();
        cout << "\"Not to mention that... " << player.getCreatureName() << " would, for lack of a better word...\"" << endl;
        cin.ignore();
        cout << "A grim aura disperses itself." << endl;
        cin.ignore();
        cout << "..." << endl;
        cin.ignore();
        cout << "\"" << player.getCreatureName() << ", I realize how unfair it is to ask you for this, but...\"" << endl;
        cin.ignore();
        cout << "\"Will you please help us save our world?\"" << endl;
        cin.ignore();
        cout << "..." << endl;
        cin.ignore();
        cout << "..." << endl;
        cin.ignore();
        cout << "..." << endl;
        cin.ignore();
        cout << player.getCreatureName() << " stares into space..." << endl;
        cin.ignore();
        cout << "...And then nods." << endl;
        cin.ignore();
        cout << "\"Very well.\"" << endl;
        cin.ignore();
        cout << "\"On behalf of all of us, and on behalf of every resident of this land, I extend my most profound gratutude, " << player.getCreatureName() << ".\"" << endl;
        cin.ignore();
        cout << "\"And to you as well, Dr. One-Behind-The-Screen.\"" << endl;
        cin.ignore();
        cout << "\"No doubt, your efforts of compassion will make this world a better place. I'll see to it personally. Thank you, dear friend.\"" << endl;
        cin.ignore();
        cout << "\"Dr. One-Behind-The-Screen, after we proceed with this plan, no doubt our ties will be severed.\"" << endl;
        cin.ignore();
        cout << "\"I will instruct the Gate Man to deliver a note to you via the \"endGameStats.txt\" file which you should find somewhere nearby.\"" << endl;
        cin.ignore();
        cout << "\"This note shall inform you of the results of what transpires here in the next couple minutes. Please look for it.\"" << endl;
        cin.ignore();
        cout << "..." << endl;
        cin.ignore();
        cout << "\"But for now, I suppose this is goodbye. Thank you again, dear friend.\"" << endl;
        cin.ignore();
        cout << "..." << endl;
        cin.ignore();
        cout << "\"ALRIGHT. EVERYONE TO THEIR STATIONS! THIS SHIP MAY GO DOWN, BUT WE'RE GOING TO MAKE SURE IT PUSHES THROUGH TO THE VERY LAST MOMENT!\"" << endl;
        cin.ignore();
        cout << "You feel all of the monsters preparing the vessel to its limit." << endl;
        cin.ignore();
        cout << "\"PREPARATIONS ARE COMPLETE! IT ALL COMES DOWN TO THIS NOW!\"" << endl; 
        cin.ignore();
        cout << "\"ON THE COUNT OF THREE!\"" << endl;
        cin.ignore();
        cout << "ONE!" << endl;
        cin.ignore();
        cout << "TWO!" << endl;
        cin.ignore();
        cout << "..." << endl;
        cin.ignore();
        cout << "THREE!!!" << endl;
        cin.ignore();
        cout << "A blinding flash." << endl;
        cin.ignore();
        printEndGameStats(mainPlayerParty.getPartyMemberAt(0), 3);
    }

    // If somehow the loop exited without any of the end game conditions being met, print an error message. For debugging purposes.
    else {
        cout << "ERROR: NO MAIN FILE ENDING CONDITIONS COULD BE MET. NO ENDING COULD BE FOUND. PRESS ENTER TO TERMINATE PROGRAM." << endl;
        cin.ignore();
    }

    return 0;
}