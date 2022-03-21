// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Project #3

/* This header file defines the Merchant class, which will be used in the final game to buy from and sell items to */
#include <iostream>
#include "Item.h"

#ifndef MERCHANT_H
#define MERCHANT_H

class Merchant {
    public:
        // Constructors
        Merchant();
        Merchant(string initialName, Item initialItemStores[], int initialItemPrices[], int arrSize);

        // Getters
        string getMerchantName();
        Item getItemAt(int index);
        int getPriceAt(int index);

        // Setters
        void setMerchantName(string newName);
        bool setItemAt(int index, Item newItem);
        void setPriceAt(int index, int newPrice);

    private:
        static const int MAX_INVENTORY_SPACE = 5;
        string merchantName;
        Item itemStores[MAX_INVENTORY_SPACE];
        int itemPrices[MAX_INVENTORY_SPACE];

};

#endif