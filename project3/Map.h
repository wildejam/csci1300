// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project #3

/* 
This map class file was taken from canvas, and edited to fit my game better.
Changes Made:
- Changed function names to represent classes in my particular game (ex. instead of getHackerCount, used getMonsterCount)
- Deleted all instances of an NPC; the only parties in my game are player, monsters, and merchants
- Removed all instances of best buy, replacing them with Merchants
- Changed the size of the map to be 10x10
- Changed the umber of monsters to be 10, and the number of merchants to be 4
- Added a "mountain" concept; Acts as barriers where the player cannot move. Should always be 20 mountains on map
- Removed spawn functions; Not needed as monsters, merchants, and monsters will be in the same place every time
- Added a removeMonsterAt() function
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
*/

#ifndef MAP_H
#define MAP_H

#include <fstream>
#include <iostream>
#include <ctype.h>

using namespace std; 

class Map
{
     private:
          static const int num_rows = 10;              // Map will always have 10 rows
          static const int num_cols = 10;              // Map will always have 10 columns
          static const int num_merchants = 4;          // Map will always have 4 merchants
          static const int num_monsters = 10;          // Map will always have 10 monsters (9 normal monsters and 1 final boss monster)
          static const int num_mountains = 20;         // Map will always have 20 mountains

          int playerPosition[2];                       // Tracks player position. Each value in the array represents x/y position of player
          int merchantPositions[num_merchants][2];     // Tracks positions of every merchant
          int monsterPositions[num_monsters][2];       // Tracks positions of every monster
          int mountainPositions[num_mountains][2];     // Tracks positions of every mountain
          char mapData[num_rows][num_cols];            // mapData array used to store characters for printing the map

          int monster_count;                           // Stores number of monsters currently on the map

     public :
          Map();                             

          void resetMap();                   

          // getters
          int getPlayerRowPosition();        
          int getPlayerColPosition();  
          int getMonsterRowPosition(int);
          int getMonsterColPosition(int);      
          int getMonsterCount();           
          int getMerchantCount();         

          int isNearMerchant();          
          int isNearMonster();              

          void displayMap();            
          void displayMoves();       

          // setters
          void setPlayerRowPosition(int); 
          void setPlayerColPosition(int);
          void setMonsterRowPosition(int, int);
          void setMonsterColPosition(int, int); 
          void setMonsterCount(int);       
 
          bool executeMove(char);  

};
 
#endif