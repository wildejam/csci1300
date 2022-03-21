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

Print a welcome message for the player. Ask them for their name and the name of their world.
Once the player enters this information, create all of the required starter objects:
    - Create a default map
    - Create Creature objects for the player, monster, merchants, and final boss. Make arrays for monsters and merchants.
        - Create item objects that each creature has
    - Create a party object, initialized with only the player in the array
    - Check for flavor text files. If flavor text files cannot be found, print error message and exit.

WHILE THE PLAYER DOES NOT WISH TO QUIT, THE PLAYER IS NOT DEAD, AND THE FINAL BOSS IS NOT DEALT WITH:
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
            - Print the player's inventory, with numbers next to each one for the player to choose
            - Prompt the player for which item they wish to use
                - If the inventory space the player chose was empty, print a message reflecting this
                - If the player chose a valid item
                    - Print a menu of party members. Ask the player for who they wish to use the item on
                    - Apply the effects of the item on the party member that the player chose
                    - If the player enters invalid input, print a message reflecting this
                - If the player wishes to exit the inventory, exit the inventory
        - Trade with merchant
            - If the player is not near a merchant, print a message reflecting this
            - If the player is near a merchant,
                - Display a custom flavor text message by reading the txt file of flavor text for each merchant.
                - Ask the player for what they wish to buy
                    - If the player's item input is invalid, print a message reflecting this
                    - If the player chooses an item that is more expensive than they can afford, print a message showing this
                    - If the player chooses an item they can afford, have them purchase the item
        - Battle monster
            - If the player is not near a monster, print a message reflecting this
            - If the player is near a monster, engage in battle with the monster.
            - If the monster that the player is battling is the final boss, walk through an additional narrative sequence before battle.
                - While neither the player or the enemy monster are dead (or out of psyche):
                    - Print a custom flavor text message by reading the txt file of flavor text for each monster. Choose one at random
                    - Prompt the player for what they wish to do. If input is invalid print a message reflecting this
                        - Attack
                            - Print a message describing how the attack went
                            - Deal a pseudo random amount of damage to the monster
                        - Befriend
                            - Print a message describing how the befriend went
                            - Deal a pseudo random amound of psyche damage to the monster
                        - Use Item
                            - Print player inventory and use item, similar to the inventory part of the main menu
                        - Check Party
                            - Print the player's party and stats. Return to the loop when done checking
                        
                    - Check if the monster is at 0 hp or 0 psyche. If so, end battle

                    - Have the monster attack the player
                        - If the attack would have killed the player, and the player has party members,
                            - Have a random monster tank the hit for the player

                    - Check if player or any party members are at 0 hp. If so print a message reflecting this. If player is at 0, end battle

                - If the player lost all health, exit every loop and go to the game over section
                - If the monster lost all health,
                    - Increase player stats to simulate them getting stronger. Add monster's health, atk, and def to the player's.
                    - Give items from monster's inventory to player
                    - Remove monster from map. Decrease monster count and replace space with empty space
                    - Print a message indicating the aftermath of the battle, if applicable
                - If the monster lost all psyche,
                    - Add the monster to the player's party. 
                    - Give items from monster's inventory to player
                    - Remove monster from map. Decrease monster count and replace space with empty space
                    - Print a message indicating the aftermath of the battle, if applicable

        - Quit
            - Print a confirmation message. If player says no, return to loop. If player says yes, end program. If invalid, ask again.

        - Invalid input (if the player enters an invalid option)
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
            cout << "Suddenly everyone around you melts into a foggy black tar. The tar melds together and is absorbed by the hysterical Emperor.";
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
            cout << "A helicopter crashes into the valley! And emerging from it.....";
            cin.ignore();
            cout << "You see Starty John! Professor Yeh rises from the wreckage! Dr. Cynth cocks her laser pistol! The Dark Dealer emerges from the darkness!";
            cin.ignore();
            cout << "Dr. Synth calls out to you:";
            cin.ignore();
            cout << "\"" << playerParty.getPartyMemberAt(0).getCreatureName() << "! I found a way to get your friends back! Just do what you always do! We'll be here to help!\"";
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
            cout << "The Emperor stares at your vessel. A look of disgust surges across his face. He takes off his dark helmet and throws it to the ground.";
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
battle() - Function used to simulate a battle in the game. Takes in the various players within the battle and modifies their stats based
    on player input and the outcome of the battle. Does not return anything.
Parameters:
    playerParty[] - The array of creatures composing the player's party. Passed by reference. (Creature)
    creaturesInParty - The amount of creatures stored in the playerParty[] array (int)
    enemy - The enemy creature that the player is fighting. Passed by reference (Creature)
    textFileName - The name of the file containing the flavor text for the monster (string)
Returns: Nothing
*/
void battle(Creature playerParty[], int creaturesInParty, Creature& enemy, string textFileName) {
    // Declare variables
    ifstream flavorText;
    int userBattleInput = 0;


    // MAIN BATTLE LOOP; WALKS THROUGH UNTIL EITHER PLAYER LOSES ALL HP OR ENEMY MONSTER LOSES ALL HP
    while (playerParty[0].getHealth() > 0 && enemy.getHealth() > 0 && enemy.getPsyche() > 0) {
        
    }

    

}

/*
finalBossBattle() - Function used to simulate the final boss battle in the game. Takes in the playerParty, modifies it to have 5 creatures, and takes in the boss.
    Modifies stats based on player actions. Is distinct from the battle() function, and has specific narrative sequences. Does not return anything.
Parameters:
    playerParty[] - The array of creatures composing the player's party. Passed by reference. (Creature)
    creaturesInParty - The amount of creatures stored in the playerParty[] array (int)
    bossEnemy - The enemy boss that the player is fighting. Passed by reference (Creature)
    textFileName - The name of the file containing the flavor text for the final boss (string)
Returns: Nothing
*/
void finalBossBattle(Creature playerParty[], int creaturesInParty, Creature& bossEnemy, string textFileName) {

}


/*
trade() - Function used to simulate trading with a merchant in the game. Takes in the player and the merchant involved, and
    takes in user input for what they wish to do during the trade. Does not return anything.
Parameters:
    player - The player who is currently trading. Passed by reference. (Creature)
    merchant - The merchant who is currently being traded with. Passed by reference. (Merchant)
Returns: Nothing
*/
void trade(Creature& player, Merchant& merchant) {

}


// Main program driver. See beginning of file for pseudocode.
int main() {



}