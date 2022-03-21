// CS1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 2 - Problem #5 - Convert teaspoons

#include <iostream>

using namespace std;

int main(){
    int teaspoons = 0;
    int tablespoons = 0;
    int cups = 0;
    const int TEASPOON_PER_TABLESPOON = 3;
    const int TEASPOON_PER_CUP = 48;

    cout << "Enter the number of teaspoons:" << endl;
    cin >> teaspoons;

    cups = teaspoons / TEASPOON_PER_CUP;
    teaspoons = teaspoons % TEASPOON_PER_CUP;
    tablespoons = teaspoons / TEASPOON_PER_TABLESPOON;    
    teaspoons = teaspoons % TEASPOON_PER_TABLESPOON;

    cout << cups << " cup(s) " << tablespoons << " tablespoon(s) " << teaspoons << " teaspoon(s) " << endl;

    return 0;
}