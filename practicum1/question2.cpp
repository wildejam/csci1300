#include <iostream>

using namespace std;

int main() {

    char inputLetter;

    cout << "Enter the first letter of the video game console: " << endl;
    cin >> inputLetter;

    switch (inputLetter) {
        case 'N':
            cout << "Console chosen: NES " << endl;
            break;
        case 'S':
            cout << "Console chosen: Super Nintendo " << endl;
            break;
        case 'X':
            cout << "Console chosen: Xbox " << endl;
            break;
        case 'P':
            cout << "Console chosen: Playstation " << endl;
            break;
        default:
            cout << "Console chosen: Invalid " << endl;
            break;
    }

    return 0;
}