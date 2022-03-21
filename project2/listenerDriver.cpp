// CSCI 1300 Fall 2021
// Author: Jamison Wilder
// Recitation 215 - Luis Mieses Gomez
// Project 2 - Problem #6

#include <iostream>
#include "Listener.h"

using namespace std;

// Function used to test the Listener class
/* Expected Output:
1,2,3,4,5,6,7,8,9,0,11,12,0,14,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
-1
-1
8
97
13
50
Shota Renwick
1
17
0
0
*/
int main() {
    // Default and parameterized constructor tests
    int listener2Songs[15] = {1,2,3,4,5,6,7,8,9,0,11,12,0,14,15};
    int listener3Songs[55] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2};
    int listener4Songs[50] = {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5};
    
    Listener listener1;                                                 // Default test
    Listener listener2 = Listener("Chris Ferrari", listener2Songs, 15); // Parameterized test
    for (int i = 0; i < 50; i++) {
        cout << listener2.getPlayCountAt(i) << ",";
    }
    cout << endl;

    Listener listener3 = Listener("Sam Keedy", listener3Songs, 55);     // Large array test
    for (int i = 0; i < 50; i++) {
        cout << listener3.getPlayCountAt(i) << ",";
    }
    cout << endl;

    Listener listener4 = Listener("Bean", listener4Songs, 50);          // Equal size arrays test
    for (int i = 0; i < 50; i++) {
        cout << listener4.getPlayCountAt(i) << ",";
    }
    cout << endl;

    cout << listener2.getPlayCountAt(-1) << endl;   // getPlayCount test: negative index
    cout << listener2.getPlayCountAt(55) << endl;   // getPlayCount test: overflow index
    cout << listener2.getPlayCountAt(7) << endl;    // getPlayCount test: normal
    cout << listener2.totalPlayCount() << endl;     // totalPlayCount test
    cout << listener2.getNumUniqueSongs() << endl;  // getNumUniqueSongs test
    cout << listener2.getSize() << endl;            // getSize test

    listener2.setListenerName("Shota Renwick");     // setListenerName test
    cout << listener2.getListenerName() << endl;

    cout << listener2.setPlayCountAt(5, 17) << endl;   // setPlayCountAt test
    cout << listener2.getPlayCountAt(5) << endl;

    cout << listener2.setPlayCountAt(-1, 52) << endl;   // setPlayCountAt test: test for invalid index value
    cout << listener2.setPlayCountAt(50, 69) << endl;   // setPlayCOuntAt test: test for invalid index value

    return 0;
}