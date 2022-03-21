------------------------
HOW TO COMPILE AND RUN
------------------------
Compile: g++ project3.cpp Item.cpp Creature.cpp Merchant.cpp Party.cpp Map.cpp
Run: ./a.out
------------------------
DEPENDENCIES
------------------------
Item.h, Creature.h, Merchant.h, Party.h, and Map.h must be in the same directory as the cpp files in 
order to compile.
monsterFlavorText.txt and merchantFlavorText.txt must also be in the same directory in order for the game to run.
------------------------
SUBMISSION INFORMATION
------------------------
CSCI1300 Fall 2021 Project 3
Author: Jamison Wilder
Recitation: 215 - Luis Mieses Gomez
Date: December 2, 2021
------------------------
ABOUT THIS PROJECT
------------------------
This project is an rpg, with an interactive world map, fightable monsters, merchants, and items. To win, you must
reach the end of the map and defeat the final boss, marked by an 'R' on the map. You may defeat monsters and get
stronger doing so, or befriend them and have them added to your party, where they will take hits for you in future
battles. If the player loses all HP, the game ends and a text file is created in the directory displaying end game statistics.
Items can be purchased from merchants and used to make your party more powerful, and to regain health.