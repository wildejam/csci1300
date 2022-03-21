// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 8 - Problem #2

#include <iostream>
#include <vector>

using namespace std;

/*
shuffle() - Takes in 2 vectors as parameters and returns a vector of values representing the 2 inputted vectors in a shuffled order.
    Shuffles the order by alternating between values of the two parameter vectors in reverse order. If one vector is shorter than the other,
    starts shuffling with the longer vector, and alternates as long as possible, then appends the data remaining. If both vectors are
    empty, returns an empty vector. If vectors are the same size, shuffling begins with the first inputted vector.
Parameters:
    vector1 - The first vector to be included in the shuffle
    vector2 - The second vector to be included in the shuffle
Returns:
    A new vector representing the shuffle as created from the two input vectors.
*/
vector<int> shuffle(vector<int> vector1, vector<int> vector2) {
    vector<int> finalVector;

    // If the two vectors are empty, return an empty vector
    if (vector1.size() == 0 && vector2.size() == 0) {
        return finalVector;
    }

    // If the two vectors are the same size, process them starting with the first inputted vector
    if (vector1.size() == vector2.size()) {
        // Loop through the parameter vectors and fill the final vector with those values alternated
        for (int i = vector1.size() - 1; i >= 0; i--) {
            finalVector.push_back(vector1.at(i));
            finalVector.push_back(vector2.at(i));
        }
        return finalVector;
    }

    // If the first vector is larger, process it starting with the first vector 
    else if (vector1.size() > vector2.size()) {
        // Loop through the two vectors until the size of the smaller vector is reached
        for (int i = vector2.size() - 1; i >= 0; i--) {
            finalVector.push_back(vector1.at(i + vector1.size() - vector2.size()));
            finalVector.push_back(vector2.at(i));
        }
        // Then append the remaining data from the larger vector to the final vector
        for (int i = vector1.size() - vector2.size() - 1; i >= 0; i--) {
            finalVector.push_back(vector1.at(i));
        }
        return finalVector;
    }

    // If the second vector is larger, proceed with the same process as above but start with the second vector
    else {
        // Loop through the two vectors until the size of the smaller vector is reached
        for (int i = vector1.size() - 1; i >= 0; i--) {
            finalVector.push_back(vector2.at(i + vector2.size() - vector1.size()));
            finalVector.push_back(vector1.at(i));
        }
        // Then append the remaining data from the larger vector to the final vector
        for (int i = vector2.size() - vector1.size() - 1; i >= 0; i--) {
            finalVector.push_back(vector2.at(i));
        }
        return finalVector;
    }
}

// This main function is used to test the shuffle() function
/* Expected Output:
10 9 8 5 6 3 4 1 2
3 -7 1 5
*empty vector*
*/
int main() {
    // Test 1: One vector is longer test case
    vector<int> v1{1,3,5,9};
    vector<int> v2{2,4,6,8,10};
    vector<int> v3 = shuffle(v1,v2);
    for (int i=0; i < v3.size(); i++) {
        cout << v3[i] << " ";
    }
    cout << endl;

    // Test 2: Vectors of equal size test case
    vector<int> v4{1,3};
    vector<int> v5{5,-7};
    vector<int> v6 = shuffle(v4,v5);
    for (int i=0; i < v6.size(); i++) {
        cout << v6[i] << " ";
    }
    cout << endl;
    
    // Test 3: Empty vectors test case
    vector<int> v7;
    vector<int> v8;
    vector<int> v9 = shuffle(v7,v8);
    for (int i=0; i < v9.size(); i++) {
        cout << v9[i] << " ";
    }
    cout << endl;

    return 0;
}