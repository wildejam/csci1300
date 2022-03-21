// CS1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 3 - Problem #6 - Price Quote - Switch Statements

#include <iostream>

using namespace std;

int main() {
    int input = 0;

    cout << "Enter Type of Sport: 1.Biking 2.Skiing 3.Fishing 4.Rock Climbing " << endl;
    cin >> input;

    switch (input) {


        case 1:
            cout << "Choose type of Equipment : 1.Mountain Bike 2.Road Bike " << endl;
            cin >> input;

            switch (input) {
                case 1:
                    cout << "Price of Mountain Bike is $550." << endl;
                    break;
                case 2:
                    cout << "Price of Road Bike is $400." << endl;
                    break;
                default:
                    cout << "Invalid Input." << endl;
                
            }
        break;


        case 2:
            cout << "Choose type of Equipment : 1.Cross-Country Skis 2.Downhill Skis " << endl;
            cin >> input;

            switch (input) {
                case 1:
                    cout << "Price of Cross-Country Skis is $300." << endl;
                    break;
                case 2:
                    cout << "Price of Downhill Skis is $500." << endl;
                    break;
                default:
                    cout << "Invalid Input." << endl;
                
            }
        break;


        case 3:
            cout << "Choose type of Equipment : 1.Regular Rod 2.Fly Fishing Rod " << endl;
            cin >> input;

            switch (input) {
                case 1:
                    cout << "Price of Regular Rod is $75." << endl;
                    break;
                case 2:
                    cout << "Price of Fly Fishing Rod is $125." << endl;
                    break;
                default:
                    cout << "Invalid Input." << endl;
                
            }
        break;


        case 4:
            cout << "Choose type of Equipment : 1.Bouldering Pad 2.Top Rope Pad " << endl;
            cin >> input;

            switch (input) {
                case 1:
                    cout << "Price of Bouldering Pad is $120." << endl;
                    break;
                case 2:
                    cout << "Price of Top Rope Pad is $60." << endl;
                    break;
                default:
                    cout << "Invalid Input." << endl;
                
            }
        break;


        default:
            cout << "Invalid Input." << endl;
    }


    return 0;
}