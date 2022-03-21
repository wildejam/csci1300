// CS1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 3 - Problem #3 - Buying kindergarten art supplies

#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    int students = 0;
    double cost = 0;
    float discount = 0;
    const double PRICE_PER_KIT = 5.50;

    cout << "Enter the number of students in the school district: " << endl;
    cin >> students;

    if (students >= 600) {
        cost = (students * PRICE_PER_KIT);
        discount = (students * (PRICE_PER_KIT -(0.75 * PRICE_PER_KIT)));
        cost = cost - discount;
        cout << fixed << setprecision(2) << "The total cost for buying art kits is $" << cost << endl;
    }

    else if (students >= 400) {
        cost = (students * PRICE_PER_KIT);
        discount = (students * (PRICE_PER_KIT -(0.8 * PRICE_PER_KIT)));
        cost = cost - discount;
        cout << fixed << setprecision(2) << "The total cost for buying art kits is $" << cost << endl;
    }

    else if (students >= 200) {
        cost = (students * PRICE_PER_KIT);
        discount = (students * (PRICE_PER_KIT -(0.85 * PRICE_PER_KIT)));
        cost = cost - discount;
        cout << fixed << setprecision(2) << "The total cost for buying art kits is $" << cost << endl;
    }

    else if (students >= 100) {
        cost = (students * PRICE_PER_KIT);
        discount = (students * (PRICE_PER_KIT -(0.9 * PRICE_PER_KIT)));
        cost = cost - discount;
        cout << fixed << setprecision(2) << "The total cost for buying art kits is $" << cost << endl;
    }

    else if (students >= 0) {
        cost = (students * PRICE_PER_KIT);
        cout << fixed << setprecision(2) << "The total cost for buying art kits is $" << cost << endl;
    }

    else {
        cout << "Invalid input." << endl;
    }

    return 0;
}
