// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project 3

// This file defines the member functions for the Merchant class

#include "Merchant.h"
#include "Item.h"
#include <fstream>

using namespace std;

/*
split(): Takes in a string and a delimiter character, splits the string into sections separated by the delimiter character, and
    populates an array with the split pieces of the string. Returns the number of pieces the string was split into. Returns
    -1 if the number of split pieces is larger than the size of the array.
Parameters:
    str - The string to be split (string)
    delimiter - The designated delimiter character (char)
    arr[] - The array where the split pieces of the string will be stored (string)
    arraySize - The size of the pieces[] array (int)
Returns: pieceCounter - The number of pieces that the string was split into (int)
*/
int split(string str, char delimiter, string arr[], int arraySize) {
    // Initialize variables for number of pieces, current position of arr[], stringLength, and temporary variable to hold a piece of a string
    int pieceCounter = 0;
    int arrayPos = 0;
    int stringLength = str.length();
    string piece;

    // Traverse the string, one character at a time
    for (int i = 0; i < stringLength; i++) {

        // If the traversal lands on the delimiter character OR the end of the string is reached...
        if (str[i] == delimiter || i == stringLength - 1) {

            // ...if this if statement was triggered by the end of the string being reached, add the final character to piece...
            if (i == stringLength - 1) {
                piece = piece + str[i];
            }

            // ... and add the current string as an array element to arr[], and reset piece to be empty. 
            // Also add 1 to the number of pieces in arr[].
            arr[arrayPos] = piece;
            arrayPos++;
            piece = "";
            pieceCounter++;


        }
        // Else, if the current string character is not equal to the delimiter, add the character to piece
        else {
            piece = piece + str[i];
        }
    }

    // If the inputted string was empty, exit the function and return 0.
    if (str == "") {
        return 0;
    }

    // If the number of pieces fits into the alotted size of the array, return pieceCounter
    if (pieceCounter <= arraySize) {
        return pieceCounter;
    }
    // Else if the number of pieces exceeds the allotted array size, return -1
    else {
        return -1;
    }
}

// Default constructor
Merchant::Merchant() {
    merchantName = "";
    Item blankItem;

    for (int i = 0; i < MAX_INVENTORY_SPACE; i++) {
        itemStores[i] = blankItem;
        itemPrices[i] = 0;
    }
}

// Parameterized constructor
Merchant::Merchant(string initialName, Item initialItemStores[], int initialItemPrices[], int arrSize) {
    merchantName = initialName;
    Item blankItem;
    for (int i = 0; i < arrSize; i++) {
        itemStores[i] = initialItemStores[i];
        itemPrices[i] = initialItemPrices[i];
    }

    for (int i = arrSize; i < MAX_INVENTORY_SPACE; i++) {
        itemStores[i] = blankItem;
        itemPrices[i] = 0;
    }
}

// Returns the max inventory space of the merchant
int Merchant::getMaxInventorySpace() {
    return MAX_INVENTORY_SPACE;
}

// Returns the name of the merchant
string Merchant::getMerchantName() {
    return merchantName;
}

// Returns the item in the merchant's inventory at the inputted index. Returns an error item if index is invalid.
Item Merchant::getItemAt(int index) {
    Item errorItem("ITEM DOES NOT EXIST", "ITEM DOES NOT EXIST", 0, 0, 0);
    if (index < 0 || index >= MAX_INVENTORY_SPACE) {
        return errorItem;
    }
    return itemStores[index];
}

// Returns the price of an item in the merchant's inventory at the inputted index. Returns -1 if index is invalid.
int Merchant::getPriceAt(int index) {
    if (index < 0 || index >= MAX_INVENTORY_SPACE) {
        return -1;
    }
    return itemPrices[index];
}

// Sets the name of the merchant
void Merchant::setMerchantName(string newName) {
    merchantName = newName;
}

// Sets an item in the merchant's inventory to be the specified item. Returns false if item could not be set.
bool Merchant::setItemAt(int index, Item newItem) {
    if (index < 0 || index >= MAX_INVENTORY_SPACE) {
        return false;
    }
    itemStores[index] = newItem;
    return true;
}

// Sets the price of an item in the merchant's inventory at the specified index
void Merchant::setPriceAt(int index, int newPrice) {
    if (index >= 0 && index < MAX_INVENTORY_SPACE) {
        itemPrices[index] = newPrice;
    }
}
