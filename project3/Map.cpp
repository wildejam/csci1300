// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project #3

/* This Map.cpp file was taken from canvas and modified to fit my game better.
Changes Made:
- Changed resetMap() to generate the same map every time it is reset
- Removed all instances of hackers, NPCS, and best buys, and replaced them with monsters and merchants
- Added functions related to mountains: spawnMountains(), etc.
- Removed spawning functions, as the same number of monsters and merchants will be in the same place every time
- Changed isLocation functions to isNear functions, returning if the player is near an object of interest, rather than on it
- Changed executeMove() and displayMoves() to prevent player from moving inside of mountains, monsters, and merchants
- Tweaked how the map is printed to print the same map every time, and used a different mapping system (mine is comparable to an x-y graph)
- Added a removeMonsterAt() function for removing monsters from the map.
*/

/* The map for this game should always be the same. 
Example for what the map should look like every time:

X - - - - - $ M - R
- - X - - X - M - -
- - M - - - - M - -
- - M - - - - M M -
- - M - - - X - M X
- - M X - M - $ M -
$ - M - - M M M M -
- - M - X - - - X -
- - M - - - - - - -
O - M - - - X - - $

O = player, $ = Merchant, X = monster, M = mountain, R = final boss
My map also utilizes a system similar to an x-y coordinate plane. In this example, the player is at row 0, column 0.
The final boss is at row 9, column 9. This is different from what was provided in the map class by default.

ALSO, each monster and merchant has a number assigned to them. Those numbers can be seen here. They are determined by the order
they are spawned in when the resetMap() function is called.

0 - - - - - 0 M - 1
- - 2 - - 3 - M - -
- - M - - - - M - -
- - M - - - - M M -
- - M - - - 4 - M 5
- - M 6 - M - 1 M -
2 - M - - M M M M -
- - M - 7 - - - 8 -
- - M - - - - - - -
O - M - - - 9 - - 3

Each number represents the number assigned to that specific monster or merchant. Merchants and monsters have seperate counters.
*/


#include "Map.h"

using namespace std; 

// Default constructor; When a map is created, initializes it to the default map state
Map::Map()
{
    resetMap();
}

// Resets the map to be in the default state; 10 monsters, player at 0,0, final boss at 9,9, and enemies/merchants at various fixed positions.
void Map::resetMap() {
    // Reset the monster count to be 10
    monster_count = 10;

    // Counters used for generating monsters, merchants, and mountains
    int mountainCounter = 0;
    int monsterCounter = 0;
    int merchantCounter = 0;

    // Traverse every single position on the map, and place all of the objects of interest at specific locations
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {

            if (i == 0 && j == 0) {
                playerPosition[0] = i;
                playerPosition[1] = j;
                mapData[i][j] = 'O';
            }

            else if (i < 8 && j == 2 || i > 5 && j == 7 || i > 2 && i < 7 && j == 8 || i == 3 && j > 4 && j < 9 || i == 4 && j == 5) {
                mountainPositions[mountainCounter][0] = i;
                mountainPositions[mountainCounter][1] = j;
                mapData[i][j] = 'M';
                mountainCounter++;
            }

            else if (i == 9 && j == 0 || i == 8 && j == 2 || i == 4 && j == 3 || i == 2 && j == 4 || i == 8 && j == 5 || 
            i == 0 && j == 6 || i == 5 && j == 6 || i == 2 && j == 8 || i == 5 && j == 9) {
                monsterPositions[monsterCounter][0] = i;
                monsterPositions[monsterCounter][1] = j;
                mapData[i][j] = 'X';
                monsterCounter++;
            }

            else if (i == 9 && j == 9) {
                monsterPositions[monsterCounter][0] = i;
                monsterPositions[monsterCounter][1] = j;
                mapData[i][j] = 'R';
                monsterCounter++;
            }

            else if (i == 9 && j == 6 || i == 4 && j == 7 || i == 3 && j == 0 || i == 0 && j == 9) {
                merchantPositions[merchantCounter][0] = i;
                merchantPositions[merchantCounter][1] = j;
                mapData[i][j] = '$';
                merchantCounter++;
            }

            // '-' Represents empty ground
            else {
                mapData[i][j] = '-';
            }
        }
    }
}

// return player's row position
int Map::getPlayerRowPosition() {
    return playerPosition[0];
}

// return player's column position
int Map::getPlayerColPosition() {
    return playerPosition[1];
}

// Return a specified monster's row position. Returns -1 if parameter was invalid.
int Map::getMonsterRowPosition(int monsterNumber) {
    if (monsterNumber >= num_monsters || monsterNumber < 0) {
        return -1;
    }
    return monsterPositions[monsterNumber][0];
}

// Return a specified monster's column position. Returns -1 if parameter was invalid.
int Map::getMonsterColPosition(int monsterNumber) {
    if (monsterNumber >= num_monsters || monsterNumber < 0) {
        return -1;
    }
    return monsterPositions[monsterNumber][1]; 
}

// Return the merchant count (will always be 4)
int Map::getMerchantCount() {
    return num_merchants;
}

// Return the current monster count, which is variable
int Map::getMonsterCount() {
    return monster_count;
}

// set player's row position to parameter row
void Map::setPlayerRowPosition(int row) {
    playerPosition[0] = row;
}

// set player's column position to parameter column
void Map::setPlayerColPosition(int col) {
    playerPosition[1] = col;
}

// Set monster's row position to parameter row. Print error message if monster number is invalid, to avoid seg faults.
void Map::setMonsterRowPosition(int monsterNumber, int row) {
    if (monsterNumber >= num_monsters || monsterNumber < 0) {
        cout << "ERROR: MONSTER NUMBER WAS INVALID. setMonsterRowPosition() FUNCTION FAILED. COULD NOT SET MONSTER POSITION." << endl;
        return;
    }
    monsterPositions[monsterNumber][1] = row;
}

// Set monster's column position to parameter column. Print error message if monster number is invalid, to avoid seg faults.
void Map::setMonsterColPosition(int monsterNumber, int column) {
    if (monsterNumber >= num_monsters || monsterNumber < 0) {
        cout << "ERROR: MONSTER NUMBER WAS INVALID. setMonsterColPosition() FUNCTION FAILED. COULD NOT SET MONSTER POSITION." << endl;
        return;
    }
    monsterPositions[monsterNumber][1] = column;
}

// Set the new monster count
void Map::setMonsterCount(int count) {
    monster_count = count;
}

// Checks if player is near Merchant, i.e, a Merchant is directly up, down, left, or right of the player. Returns the index of the Merchant that the player is next to. Returns -1 if the player is next to no Merchants.
int Map::isNearMerchant(){
    // Checks used to see if player is near a Merchant
    bool horizontalCheck = false;
    bool verticalCheck = false;
    // Iterator to keep track of which Merchant is currently being compared
    int i = 0;

    // Check every single merchant on the map to see if they are close to the player
    for (i = 0; i < num_merchants; i++) {
        // If a merchant is close to the player, set the flags to be true
        if ((merchantPositions[i][0] == playerPosition[0] - 1 || merchantPositions[i][0] == playerPosition[0] + 1) && merchantPositions[i][1] == playerPosition[1]) {
            verticalCheck = true;
        }
        else if ((merchantPositions[i][1] == playerPosition[1] - 1 || merchantPositions[i][1] == playerPosition[1] + 1) && merchantPositions[i][0] == playerPosition[0]) {
            horizontalCheck = true;
        }

        // If only one of the checks were true, a nearby merchant was found. Return the index of that merchant.
        if (verticalCheck || horizontalCheck) {
            return i;
        }
    }
        // Return -1 if no merchants were found
        return -1;
}

// Checks if player is near monster, i.e, a monster is directly up, down, left, or right of the player. Returns the index of the monster that the player is next to. Returns -1 if the player is next to no monsters.
int Map::isNearMonster(){
    // Checks used to see if player is near a monster
    bool horizontalCheck = false;
    bool verticalCheck = false;
    // Iterator to keep track of which monster is currently being compared
    int i = 0;

    // Check every single monster on the map to see if they are close to the player
    for (i = 0; i < num_monsters; i++) {
        // If a monster is close to the player, set the flags to be true
        if ((monsterPositions[i][0] == playerPosition[0] - 1 || monsterPositions[i][0] == playerPosition[0] + 1) && monsterPositions[i][1] == playerPosition[1]) {
            verticalCheck = true;
        }
        else if ((monsterPositions[i][1] == playerPosition[1] - 1 || monsterPositions[i][1] == playerPosition[1] + 1) && monsterPositions[i][0] == playerPosition[0]) {
            horizontalCheck = true;
        }

        // If only one of the checks were true, a nearby monster was found. Return the index of that monster
        if (verticalCheck || horizontalCheck) {
            return i;
        }
    }
        // If no monsters were found, return -1.
        return -1;
}

// Prints a menu of player moves based on how they can move.
// Players cannot move to a tile where there is already something else, no matter what that thing is. Player can only move to empty ground 
void Map::displayMoves(){
    // Checks used to see if the player is blocked in a certain direction
    bool upCheck = true;
    bool downCheck = true;
    bool leftCheck = true;
    bool rightCheck = true;

    // First, check if the player is at any edge of the map. If they are, they can't possibly move in that other direction
    if (playerPosition[0] == 9) {
        upCheck = false;
    }
    if (playerPosition[0] == 0) {
        downCheck = false;
    }
    if (playerPosition[1] == 9) {
        rightCheck = false;
    }
    if (playerPosition[1] == 0) {
        leftCheck = false;
    }

    // Then, check if the player is near a monster. Block any directions where there is a monster
    for (int i = 0; i < num_monsters; i++) {
        if (monsterPositions[i][0] == playerPosition[0] + 1 && monsterPositions[i][1] == playerPosition[1]) {
            upCheck = false;
        }
        if (monsterPositions[i][0] == playerPosition[0] - 1 && monsterPositions[i][1] == playerPosition[1]) {
            downCheck = false;
        }
        if (monsterPositions[i][1] == playerPosition[1] - 1 && monsterPositions[i][0] == playerPosition[0]) {
            leftCheck = false;
        }
        if (monsterPositions[i][1] == playerPosition[1] + 1 && monsterPositions[i][0] == playerPosition[0]) {
            rightCheck = false;
        }
    }

    // Then, check if the player is near a merchant. Block any directions where there is a merchant
    for (int i = 0; i < num_merchants; i++) {
        if (merchantPositions[i][0] == playerPosition[0] + 1 && merchantPositions[i][1] == playerPosition[1]) {
            upCheck = false;
        }
        if (merchantPositions[i][0] == playerPosition[0] - 1 && merchantPositions[i][1] == playerPosition[1]) {
            downCheck = false;
        }
        if (merchantPositions[i][1] == playerPosition[1] - 1 && merchantPositions[i][0] == playerPosition[0]) {
            leftCheck = false;
        }
        if (merchantPositions[i][1] == playerPosition[1] + 1 && merchantPositions[i][0] == playerPosition[0]) {
            rightCheck = false;
        }
    }

    // Then, check if the player is near a mountain. Block any directions where there is a mountain
    for (int i = 0; i < num_mountains; i++) {
        if (mountainPositions[i][0] == playerPosition[0] + 1 && mountainPositions[i][1] == playerPosition[1]) {
            upCheck = false;
        }
        if (mountainPositions[i][0] == playerPosition[0] - 1 && mountainPositions[i][1] == playerPosition[1]) {
            downCheck = false;
        }
        if (mountainPositions[i][1] == playerPosition[1] - 1 && mountainPositions[i][0] == playerPosition[0]) {
            leftCheck = false;
        }
        if (mountainPositions[i][1] == playerPosition[1] + 1 && mountainPositions[i][0] == playerPosition[0]) {
            rightCheck = false;
        }
    }

    // Print the appropriate moves based on how the player can move
    if (upCheck) {
        cout << "w (Up)" << endl;
    }
    if (downCheck) {
        cout << "s (Down)" << endl; 
    }
    if (leftCheck) {
        cout << "a (Left)" << endl; 
    }
    if (rightCheck) {
        cout << "d (Right)" << endl; 
    }
}

// This function executes the move that the player wishes to make for the player
bool Map::executeMove(char move){

    // Same check system used in displayMoves() to see if the player can move in a given direction
    bool upCheck = true;
    bool downCheck = true;
    bool leftCheck = true;
    bool rightCheck = true;

    if (playerPosition[0] == 9) {
        upCheck = false;
    }
    if (playerPosition[0] == 0) {
        downCheck = false;
    }
    if (playerPosition[1] == 9) {
        rightCheck = false;
    }
    if (playerPosition[1] == 0) {
        leftCheck = false;
    }

    for (int i = 0; i < num_monsters; i++) {
        if (monsterPositions[i][0] == playerPosition[0] + 1 && monsterPositions[i][1] == playerPosition[1]) {
            upCheck = false;
        }
        if (monsterPositions[i][0] == playerPosition[0] - 1 && monsterPositions[i][1] == playerPosition[1]) {
            downCheck = false;
        }
        if (monsterPositions[i][1] == playerPosition[1] - 1 && monsterPositions[i][0] == playerPosition[0]) {
            leftCheck = false;
        }
        if (monsterPositions[i][1] == playerPosition[1] + 1 && monsterPositions[i][0] == playerPosition[0]) {
            rightCheck = false;
        }
    }

    for (int i = 0; i < num_merchants; i++) {
        if (merchantPositions[i][0] == playerPosition[0] + 1 && merchantPositions[i][1] == playerPosition[1]) {
            upCheck = false;
        }
        if (merchantPositions[i][0] == playerPosition[0] - 1 && merchantPositions[i][1] == playerPosition[1]) {
            downCheck = false;
        }
        if (merchantPositions[i][1] == playerPosition[1] - 1 && merchantPositions[i][0] == playerPosition[0]) {
            leftCheck = false;
        }
        if (merchantPositions[i][1] == playerPosition[1] + 1 && merchantPositions[i][0] == playerPosition[0]) {
            rightCheck = false;
        }
    }

    for (int i = 0; i < num_mountains; i++) {
        if (mountainPositions[i][0] == playerPosition[0] + 1 && mountainPositions[i][1] == playerPosition[1]) {
            upCheck = false;
        }
        if (mountainPositions[i][0] == playerPosition[0] - 1 && mountainPositions[i][1] == playerPosition[1]) {
            downCheck = false;
        }
        if (mountainPositions[i][1] == playerPosition[1] - 1 && mountainPositions[i][0] == playerPosition[0]) {
            leftCheck = false;
        }
        if (mountainPositions[i][1] == playerPosition[1] + 1 && mountainPositions[i][0] == playerPosition[0]) {
            rightCheck = false;
        }
    }

    // if user inputs w, move up if it is an allowed move
    if (upCheck && tolower(move) == 'w') {
        playerPosition[0] += 1;
        return true; 
    }
    // if user inputs s, move down if it is an allowed move
    else if (downCheck && tolower(move) == 's') {
        playerPosition[0] -= 1;
        return true; 
    }
    // if user inputs a, move left if it is an allowed move
    else if (leftCheck && tolower(move) == 'a'){
        playerPosition[1] -= 1;
        return true; 
    }
    // if user inputs d, move right if it is an allowed move
    else if (rightCheck && tolower(move) == 'd'){
        playerPosition[1] += 1;
        return true; 
    }
    else {
        cout << "Invalid Move." << endl; 
        return false; 
    }
}



// Prints the 2D map
void Map::displayMap() {
    // Check every single position on the map
    // (This map's navigation system acts like an xy coordinate plane. This is why i starts at the row count - 1 and gets decremented)
    for (int i = num_rows - 1; i >= 0; i--) {
        for (int j = 0; j < num_cols; j++) {

            // Start by setting the map character to be empty ground.
            mapData[i][j] = '-';

            // If the player is at the current position, set mapData to be 'O'
            if (playerPosition[0] == i && playerPosition[1] == j) {
                mapData[i][j] = 'O';
            }
            // If a monster is at the current position, set mapData to 'X'. If it's the final boss, set mapData to 'R'
            for (int k = 0; k < num_monsters; k++) {
                if (monsterPositions[k][0] == i && monsterPositions[k][1] == j) {
                    if (i == 9 && j == 9) {
                        mapData[i][j] = 'R';
                    }
                    else {
                        mapData[i][j] = 'X';
                    }
                }
            }
            // If a merchant is at the current position, set mapData to '$'
            for (int k = 0; k < num_merchants; k++) {
                if (merchantPositions[k][0] == i && merchantPositions[k][1] == j) {
                    mapData[i][j] = '$';
                }
            }
            // If a mountain is at the current position, set mapData to 'M'
            for (int k = 0; k < num_mountains; k++) {
                if (mountainPositions[k][0] == i && mountainPositions[k][1] == j) {
                    mapData[i][j] = 'M';
                }
            }
            // Then, print out the entire map, with spaces in between for readability
            cout << mapData[i][j] << " ";
        }
        // Start a new line after every column in a row is printed
        cout << endl;
    }
    // After the map is printed, print a legend displaying what each icon on the map means
    cout << "O = Player  M = Mountain  $ = Merchant  X = Monster  R = Final Boss" << endl;
}
