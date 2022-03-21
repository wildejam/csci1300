// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project #3

/* This file defines the "Item" class, which is used to simulate items in the final game. */
#include <iostream>

using namespace std;

#ifndef ITEM_H
#define ITEM_H


class Item {
    public:
        // Constructors
        Item();     // Default constructor
        Item(string initialItemName, string initialDesc, int initialHpImpact, int initialDmgImpact, int initialDefImpact);  // Parameterized constructor

        // Getters
        string getItemName();           // Gets the name of the item
        string getItemDescription();    // Gets the description of the item
        int getHpImpact();              // Gets the HP impact of the item
        int getDmgImpact();             // Gets the Damage impact of the item
        int getDefImpact();             // Gets the defense impact of the item

        // Setters
        void setItemName(string newItemName);   // Sets the name of the item
        void setItemDescription(string newDesc);// Sets the description of the item
        void setHpImpact(int newHpImpact);      // Sets the HP impact of the item
        void setDmgImpact(int newDmgImpact);    // Sets the damage impact of the item
        void setDefImpact(int newDefImpact);    // Sets the defense impact of the item

    private:
        string itemName;             // Stores the name of the item  
        string itemDescription;      // Stores a description of the item
        int hpImpact;                // Stores the HP impact that the item has on whoever it is used on
        int dmgImpact;               // Stores the Damage impact that the item has on whoever it is used on
        int defImpact;               // Stores the Defense impact that the item has on whoever it is used on
};
#endif