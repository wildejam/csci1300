// CS1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 2 - Problem #4 - Zootopia Population

#include <iostream>
#include <algorithm>

using namespace std;

int main(){
    const int INITIAL_FOXES = 18000;
    const int INITIAL_BUNNIES = 21000;
    const int INITIAL_SLOTHS = 10000;
    const int FOX_BIRTH_RATE = 115;
    const int FOX_DEATH_RATE = 100;
    const int BUNNY_BIRTH_RATE = 90;
    const int BUNNY_DEATH_RATE = 80;
    const int SLOTH_BIRTH_RATE = 70;
    const int SLOTH_DEATH_RATE = 120;

    int foxGrowthRate = FOX_BIRTH_RATE - FOX_DEATH_RATE;
    int bunnyGrowthRate = BUNNY_BIRTH_RATE - BUNNY_DEATH_RATE;
    int slothGrowthRate = SLOTH_BIRTH_RATE - SLOTH_DEATH_RATE;
    double finalFoxes = 0;
    double finalBunnies = 0;
    double finalSloths = 0;
    double years = 0;


    cout << "Enter the number of years to estimate:" << endl;
    cin >> years;

    finalFoxes = INITIAL_FOXES + (foxGrowthRate * years);
    finalBunnies = INITIAL_BUNNIES + (bunnyGrowthRate * years);
    finalSloths = INITIAL_SLOTHS + (slothGrowthRate * years);
    finalFoxes = max(finalFoxes, 0.0);
    finalBunnies = max(finalBunnies, 0.0);
    finalSloths = max(finalSloths, 0.0);
    // The max functions prevent populations from being negative; if the population is less than 0, then the variable is set to 0 via max()

    cout << "There will be " 
        << finalFoxes << " foxes, "    
        << finalBunnies << " bunnies, and " 
        << finalSloths << " sloths in " 
        << years << " years." 
        << endl;

    return 0;
}