#include <iostream>
#include <string>
#include "Item.h"
#include "Creature.h"
#include "Party.h"

using namespace std;

// void changeItem(Party& playerParty, Item newItem) {
//     playerParty.getPartyMemberAt(0).setInventoryItemAt(0, newItem);
// }



int main() {
    Item healingpotion("healing potion", "heals you", 10, 0, 0);
    Item sword("sword", "hits things", 0, 5, 0);
    Item gauntlets("gauntlets", "protects your hands", 0, 0, 7);
    Item inventory1[3] = {healingpotion, sword, gauntlets};
    Creature Lonk("Lonk", 600, inventory1, 50, 35, 50, 40, 10, 10, 3);
    Creature party1[1] = {Lonk};
    Party testParty(party1, 1);

    cout << testParty.getPartyMemberAt(0).getInventoryItemAt(0).getItemName() << endl;

    // changeItem(testParty, sword);
    testParty.getPartyMemberAt(0).setInventoryItemAt(0, sword);

    cout << testParty.getPartyMemberAt(0).getInventoryItemAt(0).getItemName() << endl;


    cout << testParty.getPartyMemberAt(0).getHealth() << endl;
    cout << testParty.getPartyMemberAt(0).setHealth(5) << endl;
    cout << testParty.getPartyMemberAt(0).getHealth() << endl;


    return 0;
}