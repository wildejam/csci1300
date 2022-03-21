// CSCI1300 Fall 2021
// Author: Jamison Wilder
// Recitation: 215 - Luis Mieses Gomez
// Homework 5 - Problem #3

#include <iostream>

using namespace std;

/*
insert(): Traverses an array of characters and adds an extra, capitalized vowel after each existing vowel. Returns the new number of chars in array
Parameters:
    arr[] - The array to be processed
    initialChars - The number of characters in arr
    arrSize - The size of the array
    vowelAmount - The number of vowels in the array
Returns: finalChars - The new number of characters in the array
*/
int insert(char arr[], int initialChars, int arrSize, int vowelAmount) {
    int finalChars = initialChars;

    // If the array is not full and will not be overflowed after adding the extra characters,
    if (initialChars < arrSize && arrSize >= initialChars + vowelAmount) {

        // Traverse the array
        for (int i = 0; i < arrSize; i++) {

            // If the current character is a lowercase vowel,
            if (int(arr[i]) == 97 || int(arr[i]) == 101 || int(arr[i]) == 105 || int(arr[i]) == 111 || int(arr[i]) == 117) {
                // Add 1 to finalChars
                finalChars++;
                // Move every element above i up by one element (but not i itself; this is why it stops at "i + 1")
                for (int j = finalChars - 1; j > i + 1; j--) {
                    arr[j] = arr[j - 1];
                }
                // Insert the capital version of the vowel into the position just after the vowel (i + 1)
                arr[i + 1] = arr[i] - 32;
                // Skip this newly created vowel in the traverse loop
                i++;
            }
        }
        return finalChars;
    }

    // Else, if the array is full or will be overflowed after adding the extra characters, do nothing and return the original character number.
    else if (initialChars == arrSize || arrSize < initialChars + vowelAmount) {
        return finalChars;
    }

    // Return finalChars if somehow neither of the above conditions are met
    else {
        return finalChars;
    }
}

// Main function for testing insert()
int main() {

    char array[15] = {'m','i','s','s','i','s','s','i','p','p','i'};
    int characterSize = 11;
    int arraySize = 15;
    int vowelAmount = 4;

    cout << insert(array, characterSize, arraySize, vowelAmount) << endl;

    return 0;
}

