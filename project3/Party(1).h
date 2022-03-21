// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project 3

/* This header file defines the "Party" class, which is used to simulate the player's party in the final game */
#include <iostream>
#include "Creature.h"
#include "Item.h"

using namespace std;

#ifndef PARTY_H
#define PARTY_H

class Party {
    public:
        // Constructors
        Party();
        Party(Creature initialPartyMembers[], int initialPartyMembersSize);

        // Getters
        int getMaxPartyMembers();
        Creature getPartyMemberAt(int index);
        int getCurrentPartySize();
        void printAllPartyMembers();

        // Setters
        bool setPartyMemberAt(int index, Creature newMember);
        void setCurrentPartySize(int value);

    private:
        static const int MAX_PARTY_MEMBERS = 10;
        Creature partyMembers[MAX_PARTY_MEMBERS];
        int currentPartySize;

};

#endif