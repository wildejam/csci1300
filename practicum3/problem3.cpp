#include <iostream>
#include <fstream>

using namespace std;

/*
split(): Takes in a string and a delimiter character, splits the string into sections separated by the delimiter character, and
    populates an array with the split pieces of the string. Returns the number of pieces the string was split into. Returns
    -1 if the number of split pieces is larger than the size of the array.
Parameters:
    str - The string to be split (string)
    delimiter - The designated delimiter character (char)
    arr[] - The array where the split pieces of the string will be stored (string)
    arraySize - The size of the pieces[] array (int)
Returns: pieceCounter - The number of pieces that the string was split into (int)
*/
int split(string str, char delimiter, string arr[], int arraySize) {
    // Initialize variables for number of pieces, current position of arr[], stringLength, and temporary variable to hold a piece of a string
    int pieceCounter = 0;
    int arrayPos = 0;
    int stringLength = str.length();
    string piece;

    // Traverse the string, one character at a time
    for (int i = 0; i < stringLength; i++) {

        // If the traversal lands on the delimiter character OR the end of the string is reached...
        if (str[i] == delimiter || i == stringLength - 1) {

            // ...if this if statement was triggered by the end of the string being reached, add the final character to piece...
            if (i == stringLength - 1) {
                piece = piece + str[i];
            }

            // ... and add the current string as an array element to arr[], and reset piece to be empty. 
            // Also add 1 to the number of pieces in arr[].
            arr[arrayPos] = piece;
            arrayPos++;
            piece = "";
            pieceCounter++;


        }
        // Else, if the current string character is not equal to the delimiter, add the character to piece
        else {
            piece = piece + str[i];
        }
    }

    // If the inputted string was empty, exit the function and return 0.
    if (str == "") {
        return 0;
    }

    // If the number of pieces fits into the alotted size of the array, return pieceCounter
    if (pieceCounter <= arraySize) {
        return pieceCounter;
    }
    // Else if the number of pieces exceeds the allotted array size, return -1
    else {
        return -1;
    }
}


class Country {
    public:

    Country() {
        for (int i = 0; i < 50; i++) {
            countries[i] = "";
            sports[i] = "";
        }
    }

    int loadCountries(string filename) {
        string splitPieces[2];
        ifstream inputFile;
        string line;
        int i = 0;

        inputFile.open(filename);

        if (inputFile.is_open()) {

            while (getline(inputFile, line)) {
                split(line, ',', splitPieces, 2);

                countries[i] = splitPieces[0];
                sports[i] = splitPieces[1];

                i++;
            }
            return 0;
        }

        return -1;
    }

    int searchForCountry(string country) {
        int index;

        for (int i = 0; i < 50; i++) {
            if (countries[i] == country) {
                return i;
            }
        }
        return -1;
    }

    string getNationalSport(string country) {
        int index;

        for (int i = 0; i < 50; i++) {
            if (countries[i] == country) {
                return sports[i];
            }
        }
        return "";
    }


    private:
        string countries[50];
        string sports[50];

};