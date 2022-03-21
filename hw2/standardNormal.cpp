// CS1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 2 - Problem #6 - Calculating the probability in a standard normal distribution

#include <iostream>
#include <cmath>

using namespace std;

int main(){

    double x = 0.0;
    double probability = 0.0;


    cout << "Enter a value for x:" << endl;
    cin >> x;

    probability = (exp((-(pow(x , 2.0))) / 2.0))  /  sqrt(2.0 * M_PI);

    cout << "The probability at x=" << x << " is " << probability << endl;

    return 0;
}