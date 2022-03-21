// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 8 - Problem #3

#include <iostream>
#include <vector>

using namespace std;

/*
fillCumulativeSumIterative() - Takes in a positive integer, and fills a vector starting at 1 with the sum of the elements in the
    vector until the sum reaches the parameter value. Prints "Invalid input." If input is not a positive integer.
    Function also prints the elements in the vector in one line as spaced elements
Parameters:
    stopNumber - The number that the cumulative sum should stop at
Returns: Nothing
*/
void fillCumulativeSumIterative(int stopNumber) {
    // Declare variables
    vector<int> vec = {1};  // Start with a vector, initialized with a value of 1 at index 0
    int sum = 0;            // Stores the sum of all of the elements in vec<>
    int counter = 0;        // Counter used to store iterations of loop

    // Start by checking if the stopNumber is valid. Print "Invalid input." if it is not
    if (stopNumber < 1) {
        cout << "Invalid input." << endl;
        return;
    }

    // Start by printing the value of the vector at position 0. This should always print 1
    cout << vec.at(0) << " ";

    // While the sum is less than the stopNumber
    while (sum < stopNumber) {
        // Find the sum of all of the elements in the vector
        sum += vec.at(counter);

        // If the sum ends up being greater than or equal to the stopNumber, exit the while loop immediately
        if (sum >= stopNumber) {
            break;
        }

        // Else, add that value to the vector as a new element, and print it
        else {
            vec.push_back(sum);
            cout << vec.back() << " ";
        }

        // Increment the counter each time, to help with calculating the sum
        counter++;
    }
    cout << endl;
}

// Main function used for testing fillCumulativeSumIterative()
/* Expected Output:
1 1
1 1 2 4
*/
int main() {

    int n = 2;
    fillCumulativeSumIterative(n);

    n = 5;
    fillCumulativeSumIterative(n);

    return 0;
}