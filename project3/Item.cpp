// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project 3

// This file defines the member functions for the Item class
#include "Item.h"

using namespace std;

// Default constructor
Item::Item() {
    itemName = "";
    hpImpact = 0;
    dmgImpact = 0;
    defImpact = 0;
}

// Parameterized constructor
Item::Item(string initialItemName, string initialDesc, int initialHpImpact, int initialDmgImpact, int initialDefImpact) {
    itemName = initialItemName;
    itemDescription = initialDesc;
    hpImpact = initialHpImpact;
    dmgImpact = initialDmgImpact;
    defImpact = initialDefImpact;
}

// Returns the name of the item
string Item::getItemName() {
    return itemName;
}

// Returns the description of the item
string Item::getItemDescription() {
    return itemDescription;
}

// Returns the HP impact of the item
int Item::getHpImpact() {
    return hpImpact;
}

// Returns the Damage impact of the item
int Item::getDmgImpact() {
    return dmgImpact;
}

// Returns the Defense impact of the item
int Item::getDefImpact() {
    return defImpact;
}

// Sets the name of the item
void Item::setItemName(string newItemName) {
    itemName = newItemName;
}

// Sets the description of the item
void Item::setItemDescription(string newDesc) {
    itemDescription = newDesc;
}

// Sets the HP impact of the item
void Item::setHpImpact(int newHpImpact) {
    hpImpact = newHpImpact;
}

// Sets the Damage impact of the item
void Item::setDmgImpact(int newDmgImpact) {
    dmgImpact = newDmgImpact;
}

// Sets the Defense impact of the item
void Item::setDefImpact(int newDefImpact) {
    defImpact = newDefImpact;
}