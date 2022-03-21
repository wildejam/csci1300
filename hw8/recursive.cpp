// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 8 - Problem #4

#include <iostream>
#include <vector>

using namespace std;

/*
calculateSum() - This function takes in a vector and recursively calculates the sum of all of the elements in the vector.
Parameters: vec - The vector for which the sum of the elements will be found (vector<int>)
Returns: The sum of all of the elements in the vector
*/
int calculateSum(vector<int> vec) {

    // Base case: if the size of the vector is 0, the sum of that iteration is 0. Return that sum
    if (vec.size() == 0) {
        int sum = 0;
        return sum;
    }
    // Normal case: Set the sum of this iteration to be the last value in vec. Then, remove that value from the vector,
    // and pass it into calculateSum() once more, without that last value. After the base case is reached, sum
    // is returned from each iteration and is all added together.
    else {
        int sum = vec.back();
        vec.pop_back();
        sum += calculateSum(vec);
        return sum;
    }
}

/*
printVector() - Uses recursive methods to print all of the elements in a given vector
Parameters: vec - The vector for which the elements will be printed (vector<int>0)
Returns: Nothing
*/
void printVector(vector<int> vec) {
    // Base case: If the size of the vector reaches zero, every element must be done printing, so print a new line and exit the function
    if (vec.size() == 0) {
        cout << endl;
        return;
    }
    // Normal case: Print the value of the first element. Then, erase that element, and run printVector once more with this new, shorter vector.
    else {
        cout << vec.at(0) << " ";
        vec.erase(vec.begin() + 0);
        printVector(vec);
    }
}

/*
fillVector() - Fills and returns a vector with values until the cumulative sum of the values in the vector is reached. Returns the vector.
Parameters:
    vec - An initial vector to work from. Will be initialized with 1 in the final function. Passed by reference to be manipulated through recursion. (vector<int>)
    stopNumber - The number to be stopped at when the cumulative sum reaches it. (int)
Returns: The vector of values whose cumulative sum is less than the stopNumber
*/
vector<int> fillVector(vector<int>& vec, int stopNumber) {
    // Base case: If the sum of the elements in vec are larger than or equal to the stopNumber, return the vector.
    if (calculateSum(vec) >= stopNumber) {
        return vec;
    }
    // Normal case: If the sum of the elements will not be larger than or equal to the stopNumber,
    // Add that value to the end of the vector. Then, pass this new vector into fillVector() once more, with the same stop number.
    else {
        vec.push_back(calculateSum(vec));
        fillVector(vec, stopNumber);
        return vec;
    }
}

/*
fillCumulativeSumRecursive() - Takes in a stopNumber and fills and prints a vector of values whose cumulative sum is just under the stopNumber.
    Prints "Invalid input." if the stopNumber is invalid. Uses a recursive approach.
Parameters: stopNumber - The number to stop at when the cumulative sum reaches or surpasses it (int)
Returns: Nothing
*/
void fillCumulativeSumRecursive(int stopNumber) {
    // If the parameter is invalid, print "Invalid input." and exit the function immediately.
    if (stopNumber < 1) {
        cout << "Invalid input." << endl;
        return;
    }

    // Define a vector with 1 already in it, then pass it into fillVector. Print the results of fillVector.
    vector<int> vec = {1};
    vector<int> finalVec = fillVector(vec, stopNumber);
    printVector(finalVec);
}


// Main function used for testing calculateSum(), printVector(), fillVector(), and fillCumulativeSumRecursive().
/* Expected output:
15
1 2 3 4 5
1 1
1 1 2 4
*/
int main() {
    vector<int> vector1 = {1,2,3,4,5};

    cout << calculateSum(vector1) << endl;
    printVector(vector1);

    fillCumulativeSumRecursive(2);
    fillCumulativeSumRecursive(5);
}