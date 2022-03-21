// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project 3

// This main function is used to test the Map class.

#include "Map.h"

using namespace std; 

int main() {

    Map map;
    map.displayMap();
    // Expected Output: 10 4
    cout << map.getMonsterCount() << " " << map.getMerchantCount() << " " << endl;
    // Expected Output: 0 0
    cout << map.getPlayerColPosition() << " " << map.getPlayerRowPosition() << endl;

    // Expected Output:
    // w (Up)
    // d (Right)
    map.displayMoves();

    map.executeMove('w');
    map.executeMove('w');

    map.displayMap();

    // Expected Output: 1
    cout << map.isNearMerchant() << endl;

    map.executeMove('d');
    map.displayMap();

    /* Expected Output:
        w (Up)
        s (Down)
        a (Left)
    */
    map.displayMoves();
    
    // Expected Output: Invalid Move
    map.executeMove('d');
    map.displayMap();
    // Expected Output: Invalid Move
    map.executeMove('d');
    map.displayMap();

    map.executeMove('w');
    map.executeMove('w');
    map.executeMove('w');
    map.executeMove('w');
    map.executeMove('w');
    map.executeMove('w');
    map.displayMap();
    /* Expected Output:
    w (Up)
    s (Down)
    a (Left)
    */
    map.displayMoves();
    // Expected Output: 1
    cout << map.isNearMonster() << endl;

    map.setPlayerColPosition(4);
    map.setPlayerRowPosition(7);
    map.displayMap();

    /* Expected Output:
    4
    7
    */
    cout << map.getPlayerColPosition() << endl;
    cout << map.getPlayerRowPosition() << endl;

    return 0;
}
