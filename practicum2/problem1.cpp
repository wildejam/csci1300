#include <iostream>

using namespace std;

void printSeriesSkipFour(int maxValue){
    int sum = 0;
    for (int i = 1; i <= maxValue; i++){
        if (i%4 != 0){
            // If the number is not divisible by 4, add it to sum and print
            cout << i;
            sum += i;
        }
        else {
            // Print 0 when number is divisible by 4
            cout << "0";
        }
        if (i != maxValue){
            // This check is added to not print the last '+'
            cout << " + ";
        }
    }
    cout << endl;
    cout << "Result of the series is " <<sum << endl;
}




int main() {



    return 0;
}