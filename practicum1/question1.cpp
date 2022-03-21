#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    double totalCost = 0;
    double baseCost = 0;
    int minutes = 0;
    double costPerMin = 0;

    cout << "Enter the base cost for renting: " << endl;
    cin >> baseCost;
    cout << "Enter the rental time in minutes: " << endl;
    cin >> minutes;
    cout << "Enter the cost per minute: " << endl;;
    cin >> costPerMin;

    if (minutes > 60) {
        totalCost = (60 * costPerMin) + ((minutes - 60) * 0.5 * costPerMin) + baseCost;
        cout << fixed << setprecision(2) << "The total cost of the rental is: " << totalCost << endl; 
    }

    else if (minutes > 0) {
        totalCost = (minutes * costPerMin) + baseCost;
        cout << fixed << setprecision(2) << "The total cost of the rental is: " << totalCost << endl;
    }

    return 0;
}