// CS1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 2 - Problem #3 - Inches to Square Feet conversion

#include <iostream>
#include <iomanip>

using namespace std;

int main(){
    double aInchLength = 0;
    double bInchLength = 0;
    double aFootLength = 0;
    double bFootLength = 0;
    double footArea = 0;
    const double FOOT_TO_INCH_CONVERSION = (1.0/12.0);

    cout << "Enter the length of side a in inches:" << endl;
    cin >> aInchLength;
    cout << "Enter the length of side b in inches:" << endl;
    cin >> bInchLength;

    aFootLength = aInchLength * FOOT_TO_INCH_CONVERSION;
    bFootLength = bInchLength * FOOT_TO_INCH_CONVERSION;

    footArea = aFootLength * bFootLength;
    cout << fixed << setprecision(2) << "The area of the rectangular field is " << footArea << " square feet" << endl;

    return 0;
}