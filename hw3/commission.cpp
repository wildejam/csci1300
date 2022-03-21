// CS1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 3 - Problem #2 - Calculating commission

#include <iostream>
#include <iomanip>

using namespace std;

int main(){
    double revenue = 0;
    double commission = 0;

    cout << "Enter the value for revenue: " << endl;
    cin >> revenue;

    if (revenue > 65000) {
        commission = 6500 + (0.25 * (revenue - 65000));
        cout << fixed << setprecision(2) << "The commission that you earn is $" << commission << endl;
    }
    else if (revenue <= 65000 && revenue >= 0) {
        commission = 0.1 * revenue;
        cout << fixed << setprecision(2) << "The commission that you earn is $" << commission << endl;
    }
    else {
        cout << "Invalid input. " << endl;
    }

    return 0;
}