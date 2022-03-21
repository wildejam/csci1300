// CS1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 3 - Problem #4 - Boxers' weights

#include <iostream>

using namespace std;

int main() {
    int weight1 = 0;
    int weight2 = 0;
    int weight3 = 0;

    cout << "Enter boxers' weights " << endl;
    cin >> weight1 >> weight2 >> weight3;

    if (weight1 < weight2 && weight2 < weight3) {
        cout << "Ascending order" << endl;
    }

    else if (weight1 > weight2 && weight2 > weight3) {
        cout << "Descending order" << endl;
    }

    else {
        cout << "Neither" << endl;
    }
}