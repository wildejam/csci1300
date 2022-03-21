#include <iostream>

using namespace std;

int main() {
    int weight1 = 0;
    int weight2 = 0;
    int weight3 = 0;

    cout << "Enter first weight: " << endl;
    cin >> weight1;
    cout << "Enter second weight: " << endl;
    cin >> weight2;
    cout << "Enter third weight: " << endl;
    cin >> weight3;

    if (weight1 >= weight2 && weight1 >= weight3) {
        cout << "The heaviest item in this list is " << weight1 << endl;
    }

    else if (weight2 >= weight1 && weight2 >= weight3) {
        cout << "The heaviest item in this list is " << weight2 << endl;
    }

    else if (weight3 >= weight1 && weight3 >= weight2) {
        cout << "The heaviest item in this list is " << weight3 << endl;
    }
    
    return 0;
}