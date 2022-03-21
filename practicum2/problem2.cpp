#include <iostream>
#include <string>

using namespace std;

int CountVowels(string str) {

    int vowelCounter = 0;
    const string vowels = "AEIOUaeiou";


    if (str != "") {    
        for (int i = 0; i < str.length(); i++) {

            for (int j = 0; j < vowels.length(); j++) {

                if (vowels[j] == str[i]) {
                    vowelCounter++;
                }
            }
        }

        if (vowelCounter != 0) {
            return vowelCounter;
        }

        else {
            return -2;
        }

    }

    else {
        return -1;
    }


}




int main() {



    return 0;
}