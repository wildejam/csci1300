// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project 3

// This driver file is used to test the Item, Creature, Merchant, and Party classes. The tests for the Map class can be found in mapDriver.cpp
#include <iostream>
#include <string>
#include <iomanip>
#include "Item.h"
#include "Creature.h"
#include "Merchant.h"
#include "Party.h"

using namespace std;

int main() {
    // Setup
    Item healyPotion("Healy Potion", "heals u", 10, 0, 0);
    Item sword("sword", "hits things", 10, 0, 0);
    Item helmet("helmet", "safety first", 10, 0, 0);
    Item ring("ring", "put it on your finger", 10, 0, 0);
    Item bracelet("bracelet", "put it on your wrist", 10, 0, 0);
    Item necklace("necklace", "put it on your neck", 10, 0, 0);
    Item key("key", "opens something important", 10, 0, 0);
    Item diamond("diamond", "shiny", 10, 0, 0);
    Item pickaxe("pickaxe", "mines ores", 10, 0, 0);
    Item shield("shield", "protects you", 10, 0, 0);

    Item inventory1[10] = {healyPotion, sword, helmet, ring, bracelet, necklace, key, diamond, pickaxe, shield};
    int inventory1Size = 10;
    Item inventory2[2] = {helmet, key};
    int inventory2Size = 2;
    Item inventory3[5];
    int inventory3Size = 0;

    Item merchantInventory1[5] = {healyPotion, healyPotion, sword, helmet, key};
    int merchantPrices1[5] = {5, 5, 10, 10, 25};
    int merchantArr1Size = 5;
    Item merchantInventory2[3] = {bracelet, necklace, pickaxe};
    int merchantPrices2[3] = {10, 10, 20};
    int merchantArr2Size = 3;
    Item merchantInventory3[5];
    int merchantPrices3[5] = {0, 0, 0, 0, 0};
    int merchantArr3Size = 0;



    //---------------------------------Tests for Item class-------------------------------------------------------------------------------
    /* Expected Output:
    0 0 0
    Potion heals things 7 5 2
    Magical Armor super magical woo 2 1 27
    */
    // Constructor tests
    Item blankItem;
    Item potion("Potion", "heals things", 7, 5, 2);
    Item armor;

    // Getter tests
    cout << blankItem.getItemName() << " " << blankItem.getItemDescription() << " " << blankItem.getHpImpact() << " " << blankItem.getDmgImpact() << " " << blankItem.getDefImpact() << endl;
    cout << potion.getItemName() << " " << potion.getHpImpact() << " " << potion.getDmgImpact() << " " << potion.getDefImpact() << endl;

    // Setter tests
    armor.setItemName("Magical Armor");
    armor.setItemDescription("super magical woo");
    armor.setHpImpact(2);
    armor.setDmgImpact(1);
    armor.setDefImpact(27);
    cout << armor.getItemName() << " " << armor.getItemDescription() << " " << armor.getHpImpact() << " " << armor.getDmgImpact() << " " << armor.getDefImpact() << endl;

    cout << endl;
    cout << endl;
    //---------------------------------Tests for Creature class----------------------------------------------------------------------------
    /* Expected Output:
      0 0 0 0 0 0 0 10 0

    Link 50 10 10 7 7 5 6 10 10
    Healy Potion | sword | helmet | ring | bracelet | necklace | key | diamond | pickaxe | shield |
    Name                     HP             Psyche         Damage         Defense
    Link                     10/10          7/7            5              6
    The biggest emu 179 100 79 50 32 50 78 10 1 bracelet
    Name                     HP             Psyche         Damage         Defense
    The biggest emu          79/100         32/50          50             78
    */

    // Constructor tests
    Creature blankCreature;
    Creature human("Link", 50, inventory1, 10, 10, 7, 7, 5, 6, inventory1Size);
    Creature monster;

    // Getter tests
    cout << blankCreature.getCreatureName() << " " << blankCreature.getMoneyDollars() << " " << blankCreature.getMaxHealth() << " " <<
        blankCreature.getHealth() << " " << blankCreature.getMaxPsyche() << " " << blankCreature.getPsyche() << " " <<
        blankCreature.getDamage() << " " << blankCreature.getDefense() << " " << 
        blankCreature.getMaxInventorySize() << " " << blankCreature.getCurrentInventorySize() << endl;

    for (int i = 0; i < blankCreature.getCurrentInventorySize(); i++) {
        cout << blankCreature.getInventoryItemAt(i).getItemName() << " | ";
    }
    cout << endl;

    cout << human.getCreatureName() << " " << human.getMoneyDollars() << " " << human.getMaxHealth() << " " <<
        human.getHealth() << " " << human.getMaxPsyche() << " " << human.getPsyche() <<
        human.getDamage() << " " << human.getDefense() << " " << human.getMaxInventorySize() << human.getCurrentInventorySize() << endl;

    for (int i = 0; i < human.getCurrentInventorySize(); i++) {
        cout << human.getInventoryItemAt(i).getItemName() << " | ";
    }
    cout << endl;
    human.printStats();

    // Setter tests
    monster.setCreatureName("The biggest emu");
    monster.setMoneyDollars(179);
    monster.setMaxHealth(100);
    monster.setHealth(79);
    monster.setMaxPsyche(50);
    monster.setPsyche(32);
    monster.setDamage(50);
    monster.setDefense(78);

    monster.setInventoryItemAt(0, bracelet);

cout << monster.getCreatureName() << " " << monster.getMoneyDollars() << " " << monster.getMaxHealth() << " " <<
        monster.getHealth() << " " << monster.getMaxPsyche() << " " << monster.getPsyche() <<
        monster.getDamage() << " " << monster.getDefense() << " " << monster.getMaxInventorySize() << 
        monster.getCurrentInventorySize() << " " << monster.getInventoryItemAt(0).getItemName() << endl;

    monster.printStats();

    cout << endl;
    cout << endl;
    //---------------------------------Tests for Merchant class----------------------------------------------------------------------------
    /* Expected Output:
       0
    Jeff key 25
    John ITEM DOES NOT EXIST -1
    Joe shield 50
    */
    // Constructor tests
    Merchant merchant1;
    Merchant merchant2("Jeff", merchantInventory1, merchantPrices1, merchantArr1Size);
    Merchant merchant3("John", merchantInventory3, merchantPrices3, merchantArr3Size);

    // Getter tests
    cout << merchant1.getMerchantName() << " " << merchant1.getItemAt(2).getItemName() << " " << merchant1.getPriceAt(2) << endl;
    cout << merchant2.getMerchantName() << " " << merchant2.getItemAt(4).getItemName() << " " << merchant2.getPriceAt(4) << endl;
    cout << merchant3.getMerchantName() << " " << merchant3.getItemAt(7).getItemName() << " " << merchant3.getPriceAt(7) << endl;


    // Setter tests
    merchant1.setMerchantName("Joe");
    merchant1.setItemAt(0, shield);
    merchant1.setPriceAt(0, 50);
    cout << merchant1.getMerchantName() << " " << merchant1.getItemAt(0).getItemName() << " " << merchant1.getPriceAt(0) << endl;


    cout << endl;
    cout << endl;
    //---------------------------------Tests for Party class--------------------------------------------------------------------------------
    /* Expected Output:
      0
    The biggest emu 2
    Link 1
    Name                     HP             Psyche         Damage         Defense        
    Link                     10/10          7/7            5              6              

    Name                     HP             Psyche         Damage         Defense        
    Link                     10/10          7/7            5              6              
    The biggest emu          79/100         32/50          50             78          
    */
    Creature party1[10] = {human, monster};
    Creature party2[10];

    // Constructor tests
    Party lameGang;
    Party funGang(party1, 2);

    // Getter tests
    cout << lameGang.getPartyMemberAt(5).getCreatureName() << " " << lameGang.getCurrentPartySize() << endl;
    cout << funGang.getPartyMemberAt(1).getCreatureName() << " " << funGang.getCurrentPartySize() << endl;

    // Setter tests
    lameGang.setPartyMemberAt(0, human);
    lameGang.setCurrentPartySize(1);
    cout << lameGang.getPartyMemberAt(0).getCreatureName() << lameGang.getCurrentPartySize() << endl;

    lameGang.printAllPartyMembers();
    cout << endl;
    funGang.printAllPartyMembers();

    return 0;
}