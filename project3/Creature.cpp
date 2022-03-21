// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project #3

// This file defines the member functions of the Creature class

#include <iomanip>
#include "Creature.h"
#include "Item.h"

using namespace std;

// Default Constructor
Creature::Creature() {
    creatureName = "";
    moneyDollars = 0;
    maxHealth = 0;
    health = 0;
    maxPsyche = 0;
    psyche = 0;
    damage = 0;
    defense = 0;
    currentInventorySize = 0;

    for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
        inventory[i].setItemName("");
        inventory[i].setHpImpact(0);
        inventory[i].setDmgImpact(0);
        inventory[i].setDefImpact(0);
    }
}

// Parameterized Constructor
Creature::Creature(string initialName, int initialMoneyCount, Item initialInventory[], int initialMaxHealth, int initialHealth, int initialMaxPsyche, int initialPsyche, int initialDamage, int initialDefense, int numItems) {
    Item blankItem;

    creatureName = initialName;
    moneyDollars = initialMoneyCount;
    maxHealth = initialMaxHealth;
    health = initialHealth;
    maxPsyche = initialMaxPsyche;
    psyche = initialPsyche;
    damage = initialDamage;
    defense = initialDefense;
    currentInventorySize = numItems;

    for (int i = 0; i < numItems; i++) {
        inventory[i] = initialInventory[i];
    }
    for (int i = numItems; i < MAX_INVENTORY_SIZE; i++) {
        inventory[i] = blankItem;
    }
}

// Returns the maximum inventory size of the creature
int Creature::getMaxInventorySize() {
    return MAX_INVENTORY_SIZE;
}

// Returns the name of the creature
string Creature::getCreatureName() {
    return creatureName;
}

// Returns the amount of money the creature has
int Creature::getMoneyDollars() {
    return moneyDollars;
}

// Returns the max health of the creature
int Creature::getMaxHealth() {
    return maxHealth;
}

// Returns the current health of the creature
int Creature::getHealth() {
    return health;
}

// Returns the max psyche of the creature
int Creature::getMaxPsyche() {
    return maxPsyche;
}

// Returns the current psyche of the creature
int Creature::getPsyche() {
    return psyche;
}

// Returns the amount of damage that the creature does
int Creature::getDamage() {
    return damage;
}

// Returns the amount of defense that the creature has
int Creature::getDefense() {
    return defense;
}

int Creature::getCurrentInventorySize() {
    return currentInventorySize;
}

// Returns a specific item in the creature's inventory. Returns error item if index is invalid.
Item Creature::getInventoryItemAt(int index) {
    Item errorItem("ITEM DOES NOT EXIST", "ITEM DOES NOT EXIST", 0, 0, 0);
    if (index >= 0 && index < MAX_INVENTORY_SIZE) {
        return inventory[index];
    }
    else {
        return errorItem;
    }
}

// Sets the name of the creature
void Creature::setCreatureName(string newCreatureName) {
    creatureName = newCreatureName;
}

// Sets the amount of money that the creature has
void Creature::setMoneyDollars(int newMoneyDollars) {
    moneyDollars = newMoneyDollars;
}

// Sets the max health of the creature
void Creature::setMaxHealth(int newMaxHealth) {
    maxHealth = newMaxHealth;
}

// Sets the current health of the creature
void Creature::setHealth(int newHealth) {
    health = newHealth;
}

// Sets the max psyche of the creature
void Creature::setMaxPsyche(int newMaxPsyche) {
    maxPsyche = newMaxPsyche;
}

// Sets the current psyche of the creature
void Creature::setPsyche(int newPsyche) {
    psyche = newPsyche;
}

// Sets the damage that the creature does
void Creature::setDamage(int newDamage) {
    damage = newDamage;
}

// Sets the defense that the creature has
void Creature::setDefense(int newDefense) {
    defense = newDefense;
}

// Sets the current inventory size
void Creature::setCurrentInventorySize(int newSize) {
    currentInventorySize = newSize;
}

// Adds an item to the creature's inventory at the specified index. Returns false if the attempt failed.
bool Creature::setInventoryItemAt(int index, Item newItem) {
    if (index < 0 || index >= MAX_INVENTORY_SIZE) {
        return false;
    }
    inventory[index] = newItem;
    return true;
}

// Prints the stats of the creature to the console.
void Creature::printStats() {
    cout << left << setfill(' ') << setw(25) << "Name" << setw(15) << "HP" << setw(15) <<
    "Psyche" << setw(15) << "Damage" << setw(15) << "Defense" << endl;

    string healthMessage = to_string(health) + "/" + to_string(maxHealth); 
    string psycheMessage = to_string(psyche) + "/" + to_string(maxPsyche); 

    cout << left << setfill(' ') << setw(25) << creatureName << setw(15) << healthMessage << setw(15) <<
    psycheMessage << setw(15) << damage << setw(15) << defense << endl;
}
