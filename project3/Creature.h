// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project #3

/* This header file contains the definition of the "Creature" class, which is used to simulate creatures in the final game. */
#include <iostream>
#include "Item.h"

using namespace std;

#ifndef CREATURE_H
#define CREATURE_H

class Creature {
    public:
        // Constructors
        Creature();
        Creature(string initialName, int initialMoneyCount, Item initialInventory[], int initialMaxHealth,
        int initialHealth, int initialMaxPsyche, int initialPsyche, int initialDamage, int initialDefense, int numItems);

        // Getters
        int getMaxInventorySize();
        string getCreatureName();
        int getMoneyDollars();
        int getMaxHealth();
        int getHealth();
        int getMaxPsyche();
        int getPsyche();
        int getDamage();
        int getDefense();
        int getCurrentInventorySize();
        Item getInventoryItemAt(int index);

        // Setters
        void setCreatureName(string newCreatureName);
        void setMoneyDollars(int newMoneyDollars);
        void setMaxHealth(int newMaxHealth);
        void setHealth(int newHealth);
        void setMaxPsyche(int newMaxPsyche);
        void setPsyche(int newPsyche);
        void setDamage(int newDamage);
        void setDefense(int newDefense);
        void setCurrentInventorySize(int newSize);
        bool setInventoryItemAt(int index, Item newItem);

        void printStats();

    private:
        static const int MAX_INVENTORY_SIZE = 10;
        string creatureName;
        int moneyDollars;
        Item inventory[MAX_INVENTORY_SIZE];
        int maxHealth;
        int health;
        int maxPsyche;
        int psyche;
        int damage;
        int defense;
        int currentInventorySize;
};

#endif