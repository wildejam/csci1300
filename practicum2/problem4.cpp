#include <iostream>

using namespace std;


void printGoals(string names[], int goals[], int arrSizes) {

    for (int i = 0; i < arrSizes; i++) {

        if (goals[i] > 60 || goals[i] < 45) {
            cout << names[i] << " " << goals[i] << endl;
        }
    }
}




int main() {



    return 0;
}