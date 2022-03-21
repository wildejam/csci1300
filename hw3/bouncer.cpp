// CS1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 3 - Problem #1 - Bouncer

#include <iostream>

using namespace std;

int main(){
    int age = 0;

    cout << "Enter the age: " << endl;
    cin >> age;

    if (age >= 21) {
        cout << "You are allowed to go inside the bar " << endl;
    }
    else if (age >= 0) {
        cout << "You are not allowed to go inside the bar " << endl;
    }
    else {
        cout << "Invalid age " << endl;
    }

    return 0;
}