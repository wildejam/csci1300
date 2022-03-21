// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project 3

// This file defines the member functions for the Party class

#include <iomanip>
#include "Item.h"
#include "Creature.h"
#include "Party.h"

using namespace std;

// Default constructor
Party::Party() {
    Creature blankCreature;
    for (int i = 0; i < MAX_PARTY_MEMBERS; i++) {
        partyMembers[i] = blankCreature;
    }
    currentPartySize = 0;
}

// Parameterized constructor
Party::Party(Creature initialPartyMembers[], int initialPartyMembersSize) {
    Creature blankCreature;
    for (int i = 0; i < initialPartyMembersSize; i++) {
        partyMembers[i] = initialPartyMembers[i];
    }
    for (int i = initialPartyMembersSize; i < MAX_PARTY_MEMBERS; i++) {
        partyMembers[i] = blankCreature;
    }
    currentPartySize = initialPartyMembersSize;
}

// Returns the max number of party members
int Party::getMaxPartyMembers() {
    return MAX_PARTY_MEMBERS;
}

// Returns the party member at the inputted index
Creature Party::getPartyMemberAt(int index) {
    Creature blankCreature;
    if (index < 0 || index >= MAX_PARTY_MEMBERS) {
        return blankCreature;
    }
    return partyMembers[index];
}

// Returns the current party size
int Party::getCurrentPartySize() {
    return currentPartySize;
}

// Prints all party members in a table format
void Party::printAllPartyMembers() {
    cout << left << setfill(' ') << setw(25) << "Name" << setw(15) << "HP" << setw(15) <<
    "Psyche" << setw(15) << "Damage" << setw(15) << "Defense" << endl;

    for (int i = 0; i < currentPartySize; i++) {
        string name = partyMembers[i].getCreatureName();
        int health = partyMembers[i].getHealth();
        int maxHealth = partyMembers[i].getMaxHealth();
        int psyche = partyMembers[i].getPsyche();
        int maxPsyche = partyMembers[i].getMaxPsyche();
        int damage = partyMembers[i].getDamage();
        int defense = partyMembers[i].getDefense();

        string healthMessage = to_string(partyMembers[i].getHealth()) + "/" + to_string(partyMembers[i].getMaxHealth()); 
        string psycheMessage = to_string(partyMembers[i].getPsyche()) + "/" + to_string(partyMembers[i].getMaxPsyche()); 

        cout << left << setfill(' ') << setw(25) << name << setw(15) << healthMessage << setw(15) <<
        psycheMessage << setw(15) << damage << setw(15) << defense << endl;
    }
}

// Sets the party member at the inputted index to be the new party member. Returns false if action could not be completed
bool Party::setPartyMemberAt(int index, Creature newMember) {
    if (index < 0 || index > MAX_PARTY_MEMBERS) {
        return false;
    }

    partyMembers[index] = newMember;
    return true;
}

// Sets the size of the current party
void Party::setCurrentPartySize(int value) {
    currentPartySize = value;
}