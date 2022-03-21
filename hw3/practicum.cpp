// CS1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 3 - Extra Credit Question - Practicum average

#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    double score1 = 0;
    double score2 = 0;
    double score3 = 0;
    double average = 0;

    cout << "Enter practicum 1 score: " << endl;
    cin >> score1;
    cout << "Enter practicum 2 score: " << endl;
    cin >> score2;
    cout << "Enter practicum 3 score: " << endl;
    cin >> score3;

    average = (score1 + score2 + score3) / (3);
    cout << fixed << setprecision(2) << "Practicum average: " << average << endl;

    if (average >= 67.0) {
        cout << "You have a passing practicum average. " << endl;
    }

    else {
        cout << "You can retake practicums during the final. " << endl;
    }

    return 0;
}