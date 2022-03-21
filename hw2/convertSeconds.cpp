// CS1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 2 - Extra Credit Question #1 - Convert seconds

#include <iostream>

using namespace std;

int main(){
    int seconds = 0;
    int minutes = 0;
    int hours = 0;
    const int SECONDS_PER_MINUTE = 60;
    const int SECONDS_PER_HOUR = 60 * 60;

    cout << "Enter a number of seconds:" << endl;
    cin >> seconds;

    hours = seconds / SECONDS_PER_HOUR;
    seconds = seconds % SECONDS_PER_HOUR;
    minutes = seconds / SECONDS_PER_MINUTE;
    seconds = seconds % SECONDS_PER_MINUTE;

    cout << hours << " hour(s) " << minutes << " minute(s) " << seconds << " second(s) " << endl;

    return 0;
}